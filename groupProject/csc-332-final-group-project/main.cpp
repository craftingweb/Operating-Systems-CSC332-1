#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <unistd.h>

using namespace std;

void run_tree_command() {
    // TODO: implement the tree command
}

void run_list_command() {
    // TODO: implement the list command
}

void run_path_command() {
    // TODO: implement the path command
    // Get the current working directory
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        // Print the path to the terminal
        cout << "Current directory: " << cwd << endl;

        // Write the path to a file
        ofstream outfile("path.txt");
        if (outfile.is_open()) {
            outfile << cwd << endl;
            outfile.close();
            cout << "Path written to path.txt" << endl;
        }
        else {
            cerr << "Unable to write to path.txt" << endl;
        }
    }
    else {
        cerr << "Unable to get current directory" << endl;
    }
}

void run_exit_command(vector<string> commands) {
    //tracking all the commands in a vector and then passing them to exit command function. Using vector allow to add commands dynamically, unlike in an array, which is static.
    cout << "\nHistory of commands:" << endl;
    for (int i = 0; i < commands.size(); i++) { // loop through commands
        cout << commands[i] << endl; // print commands
    }

    //  implementing the exit command
    int pid = fork(); //Fork a child process which returns the PID of it. For fork() command we need include <unistd.h>. Int fork() return value 0 for child, this way to differentiate between parent and child and use in code by using 0 value for child and if it is value not 0, then it is parent.

    if (pid < 0) { // Testing for fork failing if pid less than 0
        cerr << "Fork failed for child process" << endl; // cerr is error output
        exit(0); // terminates the calling process without executing the rest of the code which is after the exit() function
    };

     if (pid == 0) { // child process is selected
        cout << "Current directory content: " << endl;
        char *args[3]; //  initialization of array of strings of command line arguments
        args[0] = "ls"; // ls -l command used to list all files & directories inside of directory,
        args[1] = "-l"; // detail information of what is inside of current directory: permission, read, write, day, size.
        args[2] = NULL; // end of array
        execvp(args[0], args); // execute an array, this system call will replace entire process, therefore line below won't be executed.
        cout << "Error 404" << endl; // testing for error
    };

    cout << endl;

    if (pid > 0) { // selecting parent process
        wait(NULL); // it will block parent execution until child finish its execution and then do parent execution. Otherwise will be chaotic execution.
        cout<<endl;
        cout << "Press RETURN key in order to exit the shell" << endl;

        while (1) { cin.ignore(); // clear buffer
            if (cin.get() == '\n') { // waiting for return key to be press
                cout << "Have a nice day!!!\n" << endl;
                break;
            }
        }
    }
}

void run_help_command() {
    cout << "Below are the commands you can use:" << endl;
    cout << "tree\t->\tCreates a directory and call it Dir0, and one empty directory, called Dir1, inside it." << endl;
    cout << "list\t->\tClear the terminal screen and print a detailed list of all content of the current directory (like ls -l) to the terminal and a file called tree.txt after creating it." << endl;
    cout << "path\t->\tPrint the current directory's path to the terminal and to a file called path.txt after creating it." << endl;
    cout << "exit\t->\tPrints a list of the last few commands to the terminal, a detailed list of all content of the current directory (like ls -l) and then exits the shell." << endl;
    cout << endl;
}

int main() {
    // Print a welcome message and run the help command
    cout << "Welcome to our command shell!" << endl;
    cout << "Run the \"help\" command to see what you can do." << endl;

    // Run the infinite shell loop until exit is called
    string command;
    vector<string> history;
    while (command != "exit") {
        // Request the command from the user
        cout << endl << "shell@user: ";
        cin >> command;

        // Store the command in the history
        history.push_back(command);

        // Run the appropriate command trigger based on the command
        if (command == "tree") {
            run_tree_command();
        } else if (command == "list") {
            run_list_command();
        } else if (command == "path") {
            run_path_command();
        } else if (command == "exit") {
            run_exit_command(history);
        } else if (command == "help") {
            run_help_command();
        } else {
            // If the command is not recognized, print an error message
            cout << "" << command << ": command not found." << endl << "Please try again or run the \"help\" command to see what you can do." << endl;
        }
    }

    return 0;
}
