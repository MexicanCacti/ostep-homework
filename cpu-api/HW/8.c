#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    int rw_pipe[2]; // rw_pipe[0] = read, rw_pipe[1] = write
    
    if(pipe(rw_pipe) == -1){
        fprintf(stderr, "Error in pip creation!\n");
        exit(1);
    }

    pid_t child1 = fork();

    if(child1 < 0){
        fprintf(stderr, "Error in child1 fork!\n");
        exit(1);
    }
    else if(child1 == 0){
        close(rw_pipe[0]);
        const char* msg = "Hello from child1!";
        write(rw_pipe[1], msg, strlen(msg));
        close(rw_pipe[1]);
        exit(0);
    }

    pid_t child2 = fork();
    if(child2 < 0){
        fprintf(stderr, "Error in child2 fork!\n");
        exit(1);
    }
    else if(child2 == 0){
        close(rw_pipe[1]);
        char msgBuffer[100];
        int bytes = read(rw_pipe[0], msgBuffer, sizeof(msgBuffer) - 1);

        if(bytes >= 0){
            msgBuffer[bytes] = '\0';
            printf("Child2 got: %s\n", msgBuffer);
        }
        else{
            fprintf(stderr, "No bytes read from pipe!\n");
        }

        close(rw_pipe[0]);
    }


    close(rw_pipe[0]);
    close(rw_pipe[1]);
    waitpid(child1, NULL, 0);
    waitpid(child2, NULL, 0);

    return 0;
}