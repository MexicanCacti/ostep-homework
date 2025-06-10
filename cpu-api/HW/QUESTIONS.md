1. Write program that calls fork(). Before calling fork, have main process access a variable & set its value. Value of variable in child process? What about if both change the variable?
- Child process takes a "snapshot" of the variable. Initially they are going to share the same value. 
- However, when the child process writes to the variable, then it will change to whatever in changed to. The parent will not see this change reflected in its variable. Vice-versa as well.
NOTE: This uses Copy-on-write where as an optimization technique, the child will share the same reference as the parent to the variable until it is written to, then it is copied.

2. Write program that opens file w/ open() sys call then forks a process. Can both the processes access the file descriptor? What happens with concurrent writes?
- Both processes are able to access the file descriptor.
- If concurrent writes occur, it would normally lead to race conditions. Meaning that its not consistent on who writes to the file first. However in this small code this doesn't occur since parent executes faster as the child has a small delay for creation. Normally, the final result is up to the scheduler.

3. Write a program using fork(). Child process should print "Hello", parent should print "goodbye". Try to ensure that the child process always prints first, do this WITHOUT calling wait()!
- Used kill(_, SIGSTOP) & kill(_, SIGCONT)

4. Write program that calls fork() then calls some form of exec() to run the program /bin/ls. Try using all variants.. execl(), execlp(), execv(), execvpe(). Why are there so many variants?
- Different variants have different use cases.
SUMMARY
-l = pass as list, -v = pass as vector (array)
-p = use PATH environment var to find executable
-e = allow specify environment variable

Maybe don't want to use memory to allocate a vector for the commands, maybe want to reuse the command vector... that could incluence whether you use vector or list!
Maybe you want to declare some environment variables... then -e very useful!

5. Now write program that uses wait() to wait for child process. What does wait return? What happens if use wait() in child?
- Wait returns the process ID of the process it was waiting for. If you call wait in the child, the ID returned is -1 & it stops waiting! -1 = error

6. Now write slight modification but with waitpid(). Why would this be useful?
- This would be useful if the program has forked multiple threads that are going to be doing several different functions using exec. Maybe the program will only want to wait until a specific function has been completed before continuing, rather than waiting for EVERY child to finish or the FIRST child to finish.
Also lets you know the status when the child terminates. Useful for knowing if killed or teminated normally!

7. Write program that creates child process then, in the child, closes the standard output (STDOUT_FILENO). What happens if the child calls printf?
- Nothing prints to the terminal if the child calls printf. However, this doesn't affect the parent. The parent can still print if the child closes it.

8. Write program that creates 2 children & pipes the standard output of one to the standard input of the other using the pipe() sys call