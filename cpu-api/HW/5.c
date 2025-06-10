#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char* argv[]){
    pid_t child_id = fork();

    if(child_id < 0){
        fprintf(stderr, "Failed to Fork!\n");
        exit(1);
    }
    else if(child_id == 0){
        printf("ChildID: %d\n", (int)getpid());
        pid_t waitId = wait(NULL);
        printf("Wait Return Val: %d\n", (int)waitId);
    }
    else{
        pid_t waitId = wait(NULL);
        printf("Wait Return Val: %d\n", (int)waitId);
    }

    return 0;
}