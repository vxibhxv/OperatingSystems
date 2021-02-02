#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<unistd.h>

int main(int argc, char**argv){
	if(argc==1){
		printf("Too few arguments!\n");
		return -1;
	}
	if(argc == 2){
		struct stat st={0};
		if(stat(argv[1],&st)==-1){
			printf("File does not exist\n");
			return -1;
		}
		if(chdir(argv[1])==0){
			printf("%s is a directory. Cannot delete\n",argv[1]);
			return -1;
		}
		if(stat(argv[1],&st)==0){
			int n=remove(argv[1]);
			//printf("%d %d\n",n,v);
			if(n<0){
				printf("Deletion failed\n");
				return -1;
			}
		}

	}
	else if(argc == 3 && strcmp(argv[1],"-i") == 0){
		printf("-i\n");
		char c;
		printf("Press 1 to confirm deletion of %s?: ",argv[1]);
		scanf("%c",&c);
		if(c !='1')
			return -1;
		struct stat st={0};
		if(stat(argv[2],&st)==-1){
			printf("File does not exist\n");
			return -1;
		}
		if(chdir(argv[2])==0){
			printf("%s is a directory. Cannot delete\n",argv[2]);
			return -1;
		}
		if(stat(argv[2],&st)==0){
			int n=remove(argv[2]);
			//printf("%d %d\n",n,v);
			if(n<0){
				printf("Deletion failed\n");
				return -1;
			}
		}
	}
	else if(argc == 3 && strcmp(argv[1],"-v") == 0){
		printf("-v\n");
		struct stat st={0};
		if(stat(argv[2],&st)==-1){
			printf("File does not exist\n");
			return -1;
		}
		if(chdir(argv[2])==0){
			printf("%s is a directory. Cannot delete\n",argv[2]);
			return -1;
		}
		if(stat(argv[2],&st)==0){
			int n=remove(argv[2]);
			//printf("%d %d\n",n,v);
			if(n<0){
				printf("Deletion failed\n");
				return -1;
			}
		}
		printf("Deleted file: %s",argv[2]);
	}
	else{
		printf("Too many arguments\n");
	}
	return 0;
}