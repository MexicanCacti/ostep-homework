#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <sys/wait.h>
#include <time.h>

#define NUM_SWITCHES 10000

void setAffinityTo0(){
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(0, &set);
    if (sched_setaffinity(0, sizeof(set), &set) == -1) {
        perror("sched_setaffinity");
        exit(1);
    }   
}

int main(int argc, char* argv[]){
    int pipe1[2];
    int pipe2[2];

    if(pipe(pipe1) == -1 || pipe(pipe2) == -1){
        perror("pipe");
        exit(1);
    }

    pid_t child = fork();
    if (child < 0) {
        perror("fork");
        exit(1);
    }

    if (child == 0) {
        setAffinityTo0();
        close(pipe1[1]); // Close write
        close(pipe2[0]); // Close read

        char buf;
        for (int i = 0; i < NUM_SWITCHES; ++i) {
            read(pipe1[0], &buf, 1);  
            write(pipe2[1], "x", 1);
        }

        exit(0);
    }

    setAffinityTo0();
    close(pipe1[0]);
    close(pipe2[1]);

    char buf = 'x';
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < NUM_SWITCHES; ++i) {
        write(pipe1[1], &buf, 1);
        read(pipe2[0], &buf, 1);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed = (end.tv_sec - start.tv_sec) +
                     (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Total time for %d context switches: %.9f seconds\n", NUM_SWITCHES, elapsed);
    printf("Average context switch time: %.3f microseconds\n", (elapsed * 1e6) / (NUM_SWITCHES * 2)); // 2 switches per iteration

    waitpid(child, NULL, 0);
    return 0;
}