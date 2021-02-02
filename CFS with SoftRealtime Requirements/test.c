#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>

int main(){

	int pid;
	/*int p;
	long t;
	printf("Enter pid: ");
	scanf("%d",&p);
	printf("Enter time: ");
	scanf("%ld",&t);*/
	struct timeval t1,t2;
	gettimeofday(&t1,NULL);
	pid = fork();
	
	if(pid<0){
		printf("Fork failed!!");
		return 1;
	}
	else if(pid == 0){
		
		
		for(int i=0;i<2000000000;i++);
		gettimeofday(&t2,NULL);
		
		printf("Child Process Time: %lf\n",(double)(t2.tv_usec-t1.tv_usec)/1000000 + (double)(t2.tv_sec-t1.tv_sec));
		
		exit(1);
	}
	else{
		
		long ret=syscall(440,pid,2);
		if(ret!=0){
			perror("Error");
			printf("Error no: %d\n",errno);
			return -1;
		}
		
		for(int i=0;i<2000000000;i++);
		gettimeofday(&t2,NULL);
		
		printf("Parent Process Time: %lf\n",(double)(t2.tv_usec-t1.tv_usec)/1000000 + (double)(t2.tv_sec-t1.tv_sec));
		
		wait(NULL);
	}
	return 0;
}