#include<stdio.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char **argv){
    //DIR *d=opendir(".");
	struct dirent **dir;
	int indx = 0;
    char *arr[100];
    int n=scandir(".",&dir,NULL,NULL);
    while(indx<n) {
        arr[indx] = dir[indx]->d_name;
        indx++;
    }
    if(argc==2 && strcmp(argv[1],"-f")==0){
        for(indx=0;indx<n;indx++){
            printf("%s\n",arr[indx]);
        }
    }
    char temp[100];
    for(int i=1;i<indx;i++){
        for(int j=1;j<indx;j++){
            if(strcmp(arr[j-1],arr[j]) > 0){
                strcpy(temp, arr[j - 1]);
                strcpy(arr[j - 1], arr[j]);
                strcpy(arr[j], temp);
            }
        }
    }
    if(argc==1){
        for(indx=0;indx<n;indx++){
            if(arr[indx][0]=='.')
                continue;
            printf("%s\n",arr[indx]);
        }
    }
    if(argc == 2 && strcmp(argv[1],"-a")==0){
        for(indx=0;indx<n;indx++){
            printf("%s\n",arr[indx]);
        }
    }
    if(argc > 2){
        printf("Invalid command! Please try again\n");
        return -1;
    }
    //printf("\n");
    //closedir(d);
	return 0;

}