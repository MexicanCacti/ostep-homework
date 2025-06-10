#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void doExecl();

void doExecle();

void doExeclp();

void doExecv();

void doExecvp();

void doExecvpe();

void forkAndCall(const char* functionName, void(*exefunc)());

int main(int argc, char* argv[]){
    forkAndCall("EXECL:", doExecl);
    forkAndCall("EXECLE:", doExecle);
    forkAndCall("EXECLP:", doExeclp);
    forkAndCall("EXECV:", doExecv);
    forkAndCall("EXECVP:", doExecvp);
    forkAndCall("EXECVPE:", doExecvpe);
}

/*
SUMMARY
-l = pass as list, -v = pass as vector (array)
-p = use PATH environment var to find executable
-e = allow specify environment variable

*/

void forkAndCall(const char* functionName, void(*exefunc)()){
    pid_t child_id = fork();

    if(child_id < 0){
        fprintf(stderr, "Failed to Fork!\n");
        exit(1);
    }
    else if(child_id == 0){
        printf("\n%s: ", functionName);
        fflush(stdout);
        exefunc();
        fprintf(stderr, "Failed to run EXEC function!\n");
        exit(1);
    }
    else{
        wait(NULL);
    }
}

void doExecl(){
    execl("/bin/ls", "ls", "-l", NULL); // Pass arguements one-by-one. Helpful for building?
}

void doExecle(){
    char* env[] = {"USER=guest", NULL};
    execle("/bin/ls", "ls", "-l", NULL, env); // Same as execl, but not can specify env to run in
}

void doExeclp(){
    execlp("ls", "ls", "-l", NULL); // Finds 'ls' path
}

void doExecv(){
    char* command[] = {"ls", "-l", NULL};
    execv("/bin/ls", command);
}

void doExecvp(){
    char* command[] = {"ls", "-l", NULL};
    execvp("ls", command);
}

void doExecvpe(){
    char* env[] = {"USER=guest", NULL};
    char* command[] = {"ls", "-l", NULL};
    execvpe("ls", command, env);
}