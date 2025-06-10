#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char* argv[]){
    char childString[8] = "hello\n";
    char parentString[10] = "goodbye\n";
    pid_t parent_id = getpid();
    pid_t child_id = fork();

    if(child_id < 0){
        fprintf(stderr, "Failed to Fork!\n");
        exit(1);
    }
    else if(child_id == 0){
        printf("%s", childString);
        kill(parent_id, SIGCONT);
    }
    else{
        kill(getpid(), SIGSTOP);
        printf("%s", parentString);
    }

}