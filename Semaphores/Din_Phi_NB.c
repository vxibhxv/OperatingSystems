#include<stdio.h>
#include<pthread.h>

#define k 5
typedef struct{
	volatile unsigned count;
	pthread_mutex_t mutex;
} my_semaphore;

void s_init(my_semaphore *sema, int val){
	sema->count=val;
	pthread_mutex_init(&sema->mutex,NULL);
}

int s_wait(my_semaphore *sema){

	if(pthread_mutex_trylock(&sema->mutex)==0){
		if(sema->count < 0){
			return 1;
		}
		sema->count--;
		pthread_mutex_unlock(&sema->mutex);
		return 0;
	}
	return 1;

}

void s_signal(my_semaphore *sema){

	pthread_mutex_lock(&sema->mutex);
	sema->count++;
	pthread_mutex_unlock(&sema->mutex);

}

void print_signal(my_semaphore *sema){

	pthread_mutex_lock(&sema->mutex);
	printf("Value : %d\n",sema->count);
	pthread_mutex_unlock(&sema->mutex);

}

void s_destroy(my_semaphore *sema){
	pthread_mutex_destroy(&sema->mutex);
}

my_semaphore fork[k],sauce[2];

int philosophers[k];


void putdown(int i){
	s_signal(&sauce[0]);
	s_signal(&sauce[1]);
	s_signal(&fork[i]);
	s_signal(&fork[(i+1)%k]);
}


void tryEat(int i){
	if(s_wait(&sauce[0]) == 0){
		if(s_wait(&sauce[1]) == 0){
			sleep(2);
			printf("Philosopher %d eats using forks %d and %d.\n",i+1,i+1,(i+1)%k+1);
			sleep(1);
			putdown(i);
		}
		else{
			s_signal(&sauce[0]);
		}
	}
}

void tryPickUp(int i){
	if(i%2==0){
		if(s_wait(&fork[i]) == 0){
			if(s_wait(&fork[(i+1)%k]) == 0){
				tryEat(i);
			}
			else{
				s_signal(&fork[i]);
			}
		}
	}
	else{
		if(s_wait(&fork[(i+1)%k]) == 0){
			if(s_wait(&fork[i]) == 0){
				tryEat(i);
			}
			else{
				s_signal(&fork[(i+1)%k]);
			}
		}
	}
}

void *philospher(void *num){
	while(1){
		int *i = num;
		tryPickUp(*i);
		tryPickUp((*i+1)%k);
		tryPickUp((*i+k-1)%k);
	}
}

int main(){
	pthread_t ph[k];
	s_init(&sauce[0],1);
	s_init(&sauce[1],1);

	for(int i=0;i<k;i++){
		s_init(&fork[i],1);
		philosophers[i]=i;
	}

	for(int i=0;i<k;i++){
		pthread_create(&ph[i],NULL,philospher, &philosophers[i]);
	}

	for(int i=0;i<k;i++){
		pthread_join(ph[i],NULL);
	}

	for(int i=0;i<5;i++)
		s_destroy(&fork[i]);
	s_destroy(&sauce[0]);
	s_destroy(&sauce[1]);
}
