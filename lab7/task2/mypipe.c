#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <wait.h>
#include <linux/limits.h>

int main(int argc, char**argv) {
    int pipefds[2];
    pid_t cpid1;
    int status1;
    pid_t cpid2;
    int status2;
    
    char *ls[3]={"ls", "-l", NULL};
    char *tail[4]={"tail", "-n", "2", NULL};
    
    pipe(pipefds);
    
    printf("parent_process>forking…\n");
    cpid1 =fork(); /*forking child1*/
    printf("parent_process>created process with id: %d\n", cpid1);
    
    if(cpid1==-1){
        perror("fork"); 
        _exit(EXIT_FAILURE);
    }
    if(cpid1==0){ /*executed by child*/
        printf("child1>redirecting stdout to the write end of the pipe…\n");
        close(STDOUT_FILENO); /*close standart so you can duplicate*/
        dup2(pipefds[1], STDOUT_FILENO);
        close(pipefds[1]); /*no need because the dup 2 it is silently closed before being reused*/
        execvp(ls[0],ls);
    
    }
    else{ /*executed by parent*/
        printf("parent_process>closing the write end of the pipe…\n");
        close(pipefds[1]); /*close so you can read until EOF*/
    }
    
    printf("parent_process>forking…\n");
    cpid2=fork(); /*forking child2*/
    printf("parent_process>created process with id: %d\n", cpid2);
    
    if(cpid2==-1){
        perror("fork"); 
        _exit(EXIT_FAILURE);
    }
    if(cpid2==0){ /*executed by child*/
        printf("child2>redirecting stdin to the read end of the pipe…\n");
        close(STDIN_FILENO); /*closes so you can duplicate*/
        dup2(pipefds[0], STDIN_FILENO);
        close(pipefds[0]); /*no need because the dup 2 it is silently closed before being reused*/
        execvp(tail[0],tail);

    }
    else{ /*executed by parent*/
        printf("parent_process>closing the read end of the pipe…\n");
        close(pipefds[0]); /*close do you can write-makes no diff*/
        }
        printf("parent_process>waiting for child processes to terminate…\n");
        waitpid(cpid1, &status1, 0);
        waitpid(cpid2, &status2, 0);
    
    return 0;
}
    
