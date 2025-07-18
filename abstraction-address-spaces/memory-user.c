#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    if(argc < 2) {
        printf("No MEGABYTE amount specified... EX: ./PROGRAM_NAME 20\n");
        return -1;
    }
    int megaBytes = atoi(argv[1]);
    int numElements = (megaBytes * 1000000) / sizeof(int);
    int* arrayPtr = (int* )calloc(numElements, sizeof(int));
    if(!arrayPtr){
        perror("Failed memory alloc");
        return -1;
    }
    
    while(true){
        for(int i = 0 ; i < numElements; ++i){
            arrayPtr[i] = 0;
        }
    }

    return 0;
}