#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

void openhistory(){
	FILE *f = fopen("/Users/vaibhav/Desktop/BasicShell/cmds.txt","w");
	fclose(f);
}
void init(char **args,int count,int in_dex){
	FILE *f = fopen("/Users/vaibhav/Desktop/BasicShell/cmds.txt","a");
	fprintf(f,"%d ",in_dex+1);
	for(int i=0;i<count;i++){
		fprintf(f,"%s ",args[i]);
	}
	fprintf(f,"\n");
	fclose(f);
	return;
}

void call_cd(char **args,int count){
	if(count == 1){
		printf("Too few arguments! Please try again\n");
		return;
	}
	if(strcmp(args[1],"/")==0)
		chdir(getenv("HOME"));
	
	else if(strcmp(args[1],"~")==0)
		chdir(getenv("usr"));

	else if(chdir(args[1])!=0)
		printf("Incorrect directory! Try using ls before executing\n");
	return;
}
void call_echo(char **args, int count){
	if(count==1){
		printf("\n");
		return;
	}
	if(args[1][0] == '-' && args[1][1] == 'n'){
		printf("%s",args[2]);
		return;
	}
	if(count == 3 && args[1][0] == '-' && args[1][1] == 'E'){
		for(int i=0;i<strlen(args[2]);i++){
			if(args[2][i]=='\\')
				i+=1;
			printf("%c",args[2][i]);
		}
		printf("\n");
		return;
	}
	printf("%s\n",args[1]);
	return;
}
void call_pwd(){
	char address[1024];
	if(getcwd(address,sizeof(address))==NULL){
		printf("Could not find directory! Please try again\n");
		return;
	}
	printf("%s\n",address);
}
void call_history(char **args, int count, int *in_dex){
	if(count == 1){
		FILE *f = fopen("/Users/vaibhav/Desktop/BasicShell/cmds.txt","r");
		char line[200];
		while(fgets(line,sizeof(line),f)){
			printf("%s ",line);
		}
		fclose(f);
		return;
	}
	else if(count == 2 && strcmp(args[1],"-c") == 0){
		FILE *f = fopen("/Users/vaibhav/Desktop/BasicShell/cmds.txt","w");
		fclose(f);
		*in_dex=0;
		return;
	}
	else if(count == 2 && strcmp(args[1],"-w") == 0){
		FILE *nf = fopen("/Users/vaibhav/Desktop/BasicShell/history.txt","w");
		FILE *f = fopen("/Users/vaibhav/Desktop/BasicShell/cmds.txt","r");
		char line[200];
		while(fgets(line,sizeof(line),f)){
			char *token=strtok(line,"\n");
			fprintf(nf,"%s ",token);
		}
		fclose(f);
		fclose(nf);
		return;
	}
	else{
		printf("Invalid command!Please try again\n");
		return;
	}

}
void call_functions(char **args,int count){
	pid_t pid;
	if(strcmp(args[0],"cd")==0)
		call_cd(args,count);
	else if(strcmp(args[0],"echo")==0)
		call_echo(args,count);
	else if(strcmp(args[0],"pwd")==0)
		call_pwd();
	else if(strcmp(args[0],"date")==0){
		pid = fork();

		if(pid<0){
			printf("Error! PLease try again!");
			return;
		}
		else if(pid == 0){
			execv("/Users/vaibhav/Desktop/BasicShell/date",args);
			printf("Failed!\n");
		}
		else{
			wait(&pid);
			return;
		}
	}
	else if(strcmp(args[0],"cat")==0){
		pid = fork();

		if(pid<0){
			printf("Error! PLease try again!");
			return;
		}
		else if(pid == 0){
			execv("/Users/vaibhav/Desktop/BasicShell/cat",args);
			printf("Failed!\n");
		}
		else{
			wait(&pid);
			return;
		}
	}
	else if(strcmp(args[0],"ls")==0){
		pid = fork();

		if(pid<0){
			printf("Error! PLease try again!");
			return;
		}
		else if(pid == 0){
			execv("/Users/vaibhav/Desktop/BasicShell/ls",args);
			printf("Failed!\n");
		}
		else{
			wait(&pid);
			return;
		}
	}
	else if(strcmp(args[0],"mkdir")==0){
		pid = fork();

		if(pid<0){
			printf("Error! PLease try again!");
			return;
		}
		else if(pid == 0){
			execv("/Users/vaibhav/Desktop/BasicShell/mkdir",args);
			printf("Failed!\n");
		}
		else{
			wait(&pid);
			return;
		}
	}
	else if(strcmp(args[0],"rm")==0){
		pid = fork();

		if(pid<0){
			printf("Error! PLease try again!");
			return;
		}
		else if(pid == 0){
			execv("/Users/vaibhav/Desktop/BasicShell/rm",args);
			printf("Failed!\n");
		}
		else{
			wait(&pid);
			return;
		}
	}
	else
		printf("Invalid command! Please try again\n");
}
int main(){
	openhistory();
	int in_dex=0;
	while(1){

		char *input;
		char **arguments=malloc(sizeof(char*)*10);

		printf("&: ");

		scanf("%[^\n]%*c", input);

    	char *argx = strtok(input, " \n\t\a");
    	int pos = 0;
    	while(argx != NULL) {
	        arguments[pos] = argx;
	        argx = strtok(NULL, " ");
	        pos++;
    	}
    	arguments[pos] = NULL;
    	init(arguments,pos,in_dex);
    	in_dex++;
    	//printf("%d %s\n",in_dex-1,history[in_dex-1]);
		if(strcmp(arguments[0],"exit")==0)
			exit(1);
		if(strcmp(arguments[0],"history")==0){
			call_history(arguments,pos,&in_dex);
			continue;
		}
		call_functions(arguments,pos);
		free(arguments);
	}
	return 0;
}