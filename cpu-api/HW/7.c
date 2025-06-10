#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    int child_id = fork();
    if(child_id < 0){
        fprintf(stderr, "Fork Failed!\n");
    }
    else if (child_id == 0) {
        close(STDOUT_FILENO);
        printf("I closed the standard output :D");
    }
    else{
        pid_t a = wait(NULL);
        printf("parent printing");
    }

    return 0;
}
