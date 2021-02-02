#include<stdio.h>
#include<pthread.h>

//https://docs.oracle.com/cd/E18752_01/html/816-5137/sync-11157.html#sync-91984 

#define k 5
typedef struct{
	volatile unsigned count;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
} my_semaphore;

void s_init(my_semaphore *sema, int val){
	sema->count=val;
	pthread_mutex_init(&sema->mutex,NULL);
	pthread_cond_init(&sema->cond,NULL);
}

void s_wait(my_semaphore *sema){

	pthread_mutex_lock(&sema->mutex);
	while(sema->count == 0)
		pthread_cond_wait(&sema->cond,&sema->mutex);
	sema->count--;
	pthread_mutex_unlock(&sema->mutex);

}

void s_signal(my_semaphore *sema){

	pthread_mutex_lock(&sema->mutex);
	sema->count++;
	pthread_cond_signal(&sema->cond);
	pthread_mutex_unlock(&sema->mutex);

}

void print_signal(my_semaphore *sema){

	pthread_mutex_lock(&sema->mutex);
	printf("Value : %d\n",sema->count);
	pthread_mutex_unlock(&sema->mutex);

}

void s_destroy(my_semaphore *sema){
	pthread_mutex_destroy(&sema->mutex);
	pthread_cond_destroy(&sema->cond);
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
	s_wait(&sauce[0]);
	s_wait(&sauce[1]);
	sleep(2);
	printf("Philosopher %d eats using forks %d and %d.\n",i+1,i+1,(i+1)%k+1);
	sleep(1);
	putdown(i);
}

void tryPickUp(int i){
	if(i%2==0){
		s_wait(&fork[i]);
		s_wait(&fork[(i+1)%k]);
	}
	else{
		s_wait(&fork[(i+1)%k]);
		s_wait(&fork[i]);
	}
	tryEat(i);
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
