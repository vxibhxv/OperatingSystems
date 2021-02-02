#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>

int main(int argc, char	**argv){
	if(argc == 1){
		printf("Too few arguments! Please try again\n");
		return -1;
	}
	if(argc == 3 && strcmp(argv[1],"-p")==0){
		struct stat st={0};
		if(stat(argv[2],&st)==0){
			printf("%s : Directory exists",argv[2]);
		}
		else if(stat(argv[2],&st)==-1){
			char *p=argv[2];
			for(;*p;p++){
				if(*p=='/'){
					*p='\0';
					mkdir(argv[2],0755);
					*p='/';
				}
				mkdir(argv[2],0755);
			}
		}
		else{
			printf("Error! Cannot create directory\n");
		}
		return 0;
	}
	int v;
	v=0;
	if(argc == 3 && strcmp(argv[1],"-v")==0){
		v=1;
		strcpy(argv[1],argv[2]);
	}
	struct stat st={0};
	if(stat(argv[1],&st)==0){
		printf("%s : Directory exists",argv[1]);
	}
	else if(stat(argv[1],&st) == -1){
		if(v){
			if(mkdir(argv[2],0755)!=0){
				printf("Invalid command! Try using the -p flag");
				return -1;
			}
			printf("Created directory %s\n",argv[2]);
		}
		else{
			if(mkdir(argv[1],0755)!=0){
				printf("Invalid command! Try using the -p flag");
				return -1;
			}
		}
	}
	else{
		printf("Error! Cannot create directory\n");
	}
	
	return 0;
}