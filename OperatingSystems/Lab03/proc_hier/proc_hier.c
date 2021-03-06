/**
 * Name: Christopher Valencia
 * Lab: Lab03
 * Date: 02/17/21
 **/
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <unistd.h>
#include    <errno.h>
#include    <sys/types.h>
#include    <sys/wait.h>

#define oops(m) {perror(m); exit(EXIT_FAILURE);}

int main() {
    pid_t pid;
        
    // fork a child process
    pid = fork();


    if (pid < 0) // error occurred
        oops("Fork Failed!");
        
    if (pid == 0) // child
    {
        
            
        pid = fork();


        if (pid < 0) // error occurred
            oops("Fork Failed!");
            
        if (pid == 0) // child
        {
            printf("I am the child %d\n", getpid());
            if (execlp("./iam", "iam", "1.1.1", NULL) < 0) 
                oops("Execlp Failed!");
        }
    
        pid = fork();

        if (pid < 0) // error occurred
        	oops("Fork Failed!");
        	
        if (pid == 0) // child
        {
            printf("I am the child %d\n", getpid());
            if (execlp("./iam", "iam", "1.1.2", NULL) < 0) 
                oops("Execlp Failed!");
        }
        
        printf("I am the child %d\n", getpid());
        if (execlp("./iam", "iam", "1.1", NULL) < 0) 
            oops("Execlp Failed!");
    }
    
    pid = fork();

    if (pid < 0) // error occurred
        oops("Fork Failed!");
        
    if (pid == 0) // child
    {
        
            
        pid = fork();


        if (pid < 0) // error occurred
            oops("Fork Failed!");
            
        if (pid == 0) // child
        {
            printf("I am the child %d\n", getpid());
            if (execlp("./iam", "iam", "1.2.1", NULL) < 0) 
                oops("Execlp Failed!");
        }
    
        pid = fork();

        if (pid < 0) // error occurred
            oops("Fork Failed!");
            
        if (pid == 0) // child
        {
            printf("I am the child %d\n", getpid());
            if (execlp("./iam", "iam", "1.2.2", NULL) < 0) 
                oops("Execlp Failed!");
        }

	printf("I am the child %d\n", getpid());
            if (execlp("./iam", "iam", "1.2", NULL) < 0) 
                oops("Execlp Failed!");

    }

        // pid > 0 ==> must be parent
        printf("I am the parent %d\n", getpid());
        /* parent will wait for the child to complete */
        if (waitpid(-1, NULL, 0) < 0)
            printf("-1 from wait() with errno = %d\n", errno);

        printf("Child terminated; parent exiting\n");
        exit(EXIT_SUCCESS);
}
