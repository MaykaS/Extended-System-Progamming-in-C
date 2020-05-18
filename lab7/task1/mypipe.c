#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <wait.h>
#include <linux/limits.h>

int main(int argc, char**argv) {
    int pipefds[2];
    pid_t cpid;
    int status;
    char *message="Hello";
    char readmessage[sizeof(message)+1];
    
    pipe(pipefds);
    cpid =fork(); /*forking a child*/
    
    if(cpid==-1){
        perror("fork"); 
        _exit(EXIT_FAILURE);
    }
    if(cpid==0){ /*executed by child*/
        close(pipefds[0]);
        write(pipefds[1], message, sizeof(message)+1);
        close(pipefds[1]);
        printf("Child process - writing : %s\n",message);
        }
    else{ /*executed by parent*/
        waitpid(cpid,&status,0);
        close(pipefds[1]);
        read(pipefds[0], readmessage ,sizeof(readmessage)+1);
        close(pipefds[0]);
        printf("Parent process - reading : %s\n",readmessage);

        }
    return 0;
}
    
