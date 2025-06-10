#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void writeToFile(char* fileName);

int main(int argc, char* argv[]) {
    char fileName[14] = "writeToMe.txt";
    writeToFile(fileName);

    return 0;
}

void writeToFile(char* fileName) {
    FILE *fptr = fopen(fileName, "w");

    if (fptr == NULL) {
        perror("Failed to open file");
        exit(1);
    }

    int child_write = fork();

    if(child_write < 0){
        fprintf(stderr, "Error Forking in: writeToFile!\n");
    }
    else if(child_write == 0){
        fprintf(fptr, "I'm a child writing!\n");
    }
    else fprintf(fptr, "I'm a parent writing!\n");

    fclose(fptr);
}
