#include <stdio.h>
#include <time.h>
#include <string.h>

int main(int argc , char **argv) {
    
    time_t now = time(&now);
    struct tm *ptm;
    if(argc == 1){
    	ptm = localtime(&now);
    	printf("Local time: %s", asctime(ptm));
    } 
    else if(strcmp(argv[1],"-u")==0 && argc == 2){
    	ptm = gmtime(&now);
    	printf("UTC time: %s", asctime(ptm));
    }
    else if(strcmp(argv[1],"-I")==0 && argc == 2){
        ptm = localtime(&now);
        printf("%d-%02d-%02d\n", ptm->tm_year+1900, ptm->tm_mon+1, ptm->tm_mday);
    }
    else{
    	printf("Invalid command! Please try again\n");
    }

    return 0;
}