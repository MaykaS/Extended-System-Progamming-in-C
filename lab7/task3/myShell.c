#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "LineParser.h"
#include <fcntl.h>
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

/*history handling*/
#define max_size 3

int size_of_list;
typedef struct history_node {
    char cmd_data[2048]; /* pointer to a struct containing the offset and the value of the bytes in each of the files*/
    struct history_node *next;
    struct history_node *prev;
}history_node;

/*print*/
void list_print(history_node *history_head, FILE* output){
    int i=size_of_list-1;   
    history_node *current= history_head; /*pointer to the beginning*/
    while(current && i>=0){ /*as long as there is a current*/
       fprintf(output,"%d. %s \n",i, current->cmd_data);
        current=current->next;
        i--;
    }
}



history_node *deleteFromHistory(history_node *history_head,int delete_index){
    history_node *current = history_head;
    int i=0;

    while(i<(size_of_list-delete_index) && current){
            current=current->next;
            i++;
    }
    if(current->next==NULL){
        current->prev->next=NULL;
        free(current);
    }
    else if(current->prev==NULL){
        current->next->prev=NULL;
        free(current);
    }
    else{
        current->prev->next=current->next;
        current->next->prev=current->prev;
        free(current);
    }
    size_of_list--;
    
    return history_head;
}
/*add to list*/

history_node* list_append(history_node* history_head, char* data){
        
    history_node* next_node = malloc(sizeof(history_node));
    strcpy (next_node->cmd_data,data);

    if (history_head == NULL){
        next_node->prev = NULL;
        next_node->next = NULL;
    } else {
        history_head->prev = next_node;
        next_node->next = history_head;
    }
    
    if(size_of_list==max_size){
        history_head=deleteFromHistory(history_head, 1);
    }
    size_of_list++;
    return next_node;
}

history_node* handelExc(cmdLine **pCmdLine, history_node *history_head,int exc_index){
    int i=size_of_list-exc_index-1;
    history_node *current=history_head;
    while(current && i>0){
        current=current->next;
        i--;
    }
    
    freeCmdLines(*pCmdLine);
    *pCmdLine=parseCmdLines(current->cmd_data);/*&does the execute*/
    
    return current;
}

/* Free the memory allocated by and for the list. */
void list_free(history_node *history_head){ 
    history_node *current=history_head;
    history_node *tmp;
    while(current){
        tmp=current->next;
        free(current);
        current=tmp;
    }
}

#define MAX_PATH 260
void execute_pipe_command(cmdLine *pCmdLine){
    
    
    int pipefds[2];
    pid_t cpid1;
    int status1;
    pid_t cpid2;
    int status2;
    
    
    pipe(pipefds);
    
    printf("parent_process>forking…\n");
    cpid1 =fork(); /*forking child1*/
    printf("parent_process>created process with id: %d\n", cpid1);
    
    if(cpid1==-1){
        perror("fork"); 
        _exit(EXIT_FAILURE);
    }
    if(cpid1==0){ /*executed by child*/
        close(STDOUT_FILENO);
        dup2(pipefds[1], STDOUT_FILENO);
        close(pipefds[1]);
        execvp(pCmdLine->arguments[0],pCmdLine->arguments);
        
    }
    else{ /*executed by parent*/
        close(pipefds[1]);
    }
    
    printf("parent_process>forking…\n");
    cpid2=fork(); /*forking child2*/

    
    if(cpid2==-1){
        perror("fork"); 
        _exit(EXIT_FAILURE);
    }
    if(cpid2==0){ /*executed by child*/
        close(STDIN_FILENO);
        dup2(pipefds[0], STDIN_FILENO);
        close(pipefds[0]);
        execvp(pCmdLine->next->arguments[0],pCmdLine->next->arguments);

    }
    else{ /*executed by parent*/
        close(pipefds[0]);
        }
        waitpid(cpid1, &status1, 0);
        waitpid(cpid2, &status2, 0);
        
}


/*execute func*/
int execute(cmdLine *pCmdLine){
    pid_t cpid;
    int status;
    cpid =fork(); /*forking a child*/
    if(cpid==-1){
        perror("fork"); 
        _exit(EXIT_FAILURE);
    }
    if(cpid==0){ /*executed by child*/
       if (pCmdLine->outputRedirect != NULL) {
            close(STDOUT_FILENO);
            int file_descriptor = open(pCmdLine->outputRedirect, O_WRONLY); /*write only*/

        }
        if (pCmdLine->inputRedirect != NULL) {
            close(STDIN_FILENO);
            int file_descriptor = open(pCmdLine->inputRedirect, O_RDONLY); /*read only*/

        }
        if (pCmdLine) {
            execvp(pCmdLine->arguments[0], pCmdLine->arguments);
        }
        perror("Error");
        exit(EXIT_FAILURE);
    } else if(pCmdLine->blocking ==1){ /*executed by parent / if not terminated*/
            waitpid(cpid,&status,0); /*waits until the child terminates*/
            
        }
        return status;
    }

/*replace ~ with HOME*/
void _replace(cmdLine *pCmdLine){
    char *HOME= getenv("HOME"); /*my home dir*/
    int i;
    for(i=0; i<pCmdLine->argCount; i++){
        if(strcmp(pCmdLine->arguments[i], "~")==0){
            printf("Home: %s\n",HOME);
            replaceCmdArg(pCmdLine,i,HOME);
        }
        
        else if(pCmdLine->arguments[i][0] =='~'){
            char *to_replace=pCmdLine->arguments[i];
            to_replace++; /*get out the ~*/
            char *HOME_replce=malloc(strlen(HOME)+strlen(to_replace));
            HOME_replce=getenv("HOME");
            strcat(HOME_replce,to_replace); /*put new instead of ~ we found*/
            printf("New Home: %s\n",HOME_replce);
            replaceCmdArg(pCmdLine,i,HOME_replce);
        }
    }
}

int main(int argc, char **argv){
    FILE *output=stdout;
    struct history_node *history_head=NULL;
    size_of_list=0;
    int quit=-1;
    int delete_index;
    while(quit!=0){
        
        /*print curr dir*/
        char buf[MAX_PATH];
        getcwd(buf, sizeof(buf));
        printf("\n directory: %s", buf); 
        /*read line from user*/
        char u_string[2048]; /*user input*/
        fgets(u_string,2048,stdin);
        if(strcmp(u_string,"\n")==0)
            printf("\n");
        else{
            cmdLine *head;
            head=parseCmdLines(u_string);
            if (head->next!=NULL)
                execute_pipe_command(head);
            _replace(head); /*replace ~ with HOME dir*/
            if(u_string[0]=='!'){
                /*TODO-change a bit*/
                printf("! mark found\n");
                int exc_index=atoi(head->arguments[0]+1);
                printf("exc_index: %d\n",exc_index);
                history_node *exc_node=NULL;
                exc_node=handelExc(&head,history_head,exc_index);
                history_head=list_append(history_head,exc_node->cmd_data);
            } else{
                history_head=list_append(history_head,u_string);
            }
            quit= strcmp(head->arguments[0],"quit");
            /*parse the inpute*/
        
            if(strcmp(head->arguments[0],"cd")==0){/*he wants to change dir*/
                if(chdir(head->arguments[1]))/*if no such dir*/
                    perror("cd");
            }
            else if(strcmp(head->arguments[0],"history")==0){
                if ((head->argCount > 2) &&  (strcmp(head->arguments[1],"-d") == 0)){
                    delete_index=atoi(head->arguments[2])+1;
                    history_head=deleteFromHistory(history_head,delete_index);
                    perror("delete");
                } else{
                    list_print(history_head,output);
                    perror("history");
                }
            }
            else if(quit!=0){
                /*execute*/
                    execute(head);
            }
            freeCmdLines(head);
        }
    }
    list_free(history_head);
    return 0;
}
