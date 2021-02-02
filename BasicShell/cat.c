#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main(int argc, char **argv){
	int file,size;
	char buf[50];

	if(argc == 1){
		printf("Too few arguments! Please try again\n");
		return -1;
	}
	else if(strcmp(argv[1],"-n")==0 && argc == 3){
		file = open(argv[2],O_RDONLY);
		if(file == -1){
			printf("Error opening file!\n");
			return -1;
		}
		int count=2;
		printf("1. ");
		while((size = read(file,buf,50)) > 0){
			for(int i=0;i<size;i++){
				if(buf[i]=='\n')
					printf("\n%d. ",count++);
				else
					printf("%c",buf[i]);
			}
		}

		close(file);
	}
	else if(strcmp(argv[1],"-e")==0 && argc == 3){
		file = open(argv[2],O_RDONLY);
		if(file == -1){
			printf("Error opening file!\n");
			return -1;
		}
		int count=2;
		while((size = read(file,buf,50)) > 0){
			for(int i=0;i<size;i++){
				if(buf[i]=='\n')
					printf("$\n");
				else
					printf("%c",buf[i]);
			}
		}

		close(file);
	}
	else if(argc == 2){
		file = open(argv[1],O_RDONLY);
		if(file == -1){
			printf("Error opening file!\n");
			return -1;
		}
		int count=2;
		while((size = read(file,buf,50)) > 0){
			write(1,&buf,size);
		}

		close(file);
	}
	else{
		printf("Invalid arguments");
		return -1;
	}

	return 0;
}