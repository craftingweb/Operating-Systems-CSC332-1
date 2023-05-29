
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    char *myargs[3]; // Define Arg (ls -F)
    char *myargs2[2]; // Define Second Arg (nl)

    int mypipe[2]; // Creating Array For Pipe

    if (pipe(mypipe) == -1){ // Initizing Pipe and Testing For Fails
        fprintf(stderr, "Pipe Failed");
        return 1;
    }

    int pid = fork(); // Creates 1 Child.
    if (pid < 0){ // Test For Fork Failed
        fprintf(stderr, "Fork Failed");
        return 1;
    }

    if (pid > 0) {
        // Parent
        //close(mypipe[0]); // Close Reading
        //close(mypipe[1]); // Close Writing
        //printf("Parent \n");
        int pid2 = fork(); //Creates Another Child

        if (pid2 < 0){ // Test For Fork Failed
            fprintf(stderr, "Fork Failed");
            return 1;
        }

        else if (pid2 > 0){
            // Parent
            wait(NULL); // Wait For First Child Process to Finish
            close(mypipe[1]); // Close Writing
            wait(NULL); // Wait For Second Child Process to Finish
            //printf("Done");
        }

        else if (pid2 == 0){ // Second Child from the Parent.
            // First Child
            //printf("Child1 \n");
            close(1); // Close stdout
            close(mypipe[0]); // Close Reading, Don't Need It
            myargs[0] = "ls";   // Perform ls
            myargs[1] = "-F"; // Perform -F
            myargs[2] =  NULL; // Marks End of Array
            dup(mypipe[1]); // Making stdout the Same as mypipe[1]
            //write(mypipe[1], myargs, sizeof(myargs)); // Write to Pipe
            //close(mypipe[1]); //Close Writing
            execvp(myargs[0], myargs); // Execute ls -F
            //execlp("ls","ls",NULL);
            printf("This Shouldn't Run \n"); // In Case of Failure
        }
        else {
            printf("This Shouldn't Run \n"); // In Case of Failure
        }
    }
    else if (pid == 0){
        // Second Child
        //printf("Child2 \n");
        //close(0); // Close stdin
        //close(mypipe[1]); // Close Writing, Don't Need It
        //dup(mypipe[0]); // Making stdin the Same as MyPipe[0]
        //read(mypipe[0], myargs, sizeof(myargs)); // Read the Pipe
        //printf("Back to Parent \n");
        close(0); // Close stdin
        close(mypipe[1]); // Close Writing, Don't Need It
        dup(mypipe[0]); // Making stdin the Same as MyPipe[0], which was taken from the first child
        close(mypipe[0]); // Close Reading, Already Read from dup, could also run without it
        myargs2[0] = "nl"; // Perform nl
        myargs2[1] = NULL; // Marks End of Array
        execvp(myargs2[0], myargs2); // Execute nl
        //close(mypipe[0]); // Close Reading
        //printf("%s \n", myargs[0]);
        //printf("%s \n", myargs[1]);
        //execlp("nl","nl",NULL);
        printf("This Shouldn't Run \n"); // In Case of Failure
    }
    else{
        printf("This Shouldn't Run \n"); // In Case of Failure
    }
    return 0;
}
