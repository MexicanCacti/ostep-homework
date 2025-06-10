#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int x = 100;
    x = 5;
    int child_id = fork();

    if(child_id < 0){
        fprintf(stderr, "Fork Failed!\n");
    }
    else if (child_id == 0) {
        x = 50;
        printf("child (pid:%d) Integer Val: %d\n", (int) getpid(), x);
    }
    else{
        x = 10;
        printf("parent Integer Val: %d\n", x);
    }

    return 0;
}
