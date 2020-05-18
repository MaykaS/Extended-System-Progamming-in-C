#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "LineParser.h"
/*
typedef struct cmdLine
{
    char * const arguments[MAX_ARGUMENTS]; 
    int argCount;		
    char const *inputRedirect;	
    char const *outputRedirect;	
    char blocking;	
    int idx;		
    struct cmdLine* next;	 
} cmdLine;
*/

#define PATH_MAX 4096 

/*execute func*/
int execute(cmdLine *pCmdLine){
    pid_t child_pid;
    int child_status;
    child_pid = fork();

    if (child_pid==0) {
        execvp(pCmdLine->arguments[0], pCmdLine->arguments);
        perror("execvp");
        _exit(EXIT_FAILURE);
    } else {
        if (pCmdLine->blocking == 1) {
            waitpid(child_pid, &child_status, 0);
        }
        return child_status;
    }
}

/*replace ~ with HOME*/
void _replace(cmdLine *pCmdLine){
    char *HOME= getenv("HOME"); /*my home dir*/
    int i;
    for(i=0; i<pCmdLine->argCount; i++){
        if(strcmp(pCmdLine->arguments[i], "~")==0){
            printf("Home is: %s\n", HOME);
            replaceCmdArg(pCmdLine,i,HOME);
        }
        else if(pCmdLine->arguments[i][0] =='~'){
            char *to_replace=pCmdLine->arguments[i];
            to_replace++; /*get out the ~*/
            char *HOME_replce=malloc(strlen(HOME)+strlen(to_replace));
            HOME_replce=getenv("HOME");
            strcat(HOME_replce,to_replace); /*put new instead of ~ we found*/
            printf("Now is: %s\n", HOME_replce);
            replaceCmdArg(pCmdLine,i,HOME_replce);
        }
    }
}

int main(int argc, char **argv){
    int quit=-1;
    while(quit!=0){
        /*print curr dir*/
        char buf[PATH_MAX];
        getcwd(buf, sizeof(buf));
        printf("\n directory: %s", buf); 
        /*read line from user*/
        char u_string[2048]; /*user input*/
        fgets(u_string,2048,stdin);
        if(strcmp(u_string,"\n")==0)
            printf("\n");
        /*parse the inpute*/
        else{
            cmdLine *head;
            head=parseCmdLines(u_string);
            _replace(head); /*replace ~ with HOME dir*/
            quit= strcmp(head->arguments[0],"quit"); /*check for quit*/
            if(strcmp(head->arguments[0],"cd")==0){/*he wants to change dir*/
                chdir(head->arguments[1]);/*returns -1 on error*/
                perror("cd");
            }
            else if(quit!=0){
                /*execute*/
                execute(head);
            }
            freeCmdLines(head);
        }
    }
    return 0;
}
