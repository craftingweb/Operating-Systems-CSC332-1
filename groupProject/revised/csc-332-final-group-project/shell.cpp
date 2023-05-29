#include <iostream>
#include <vector>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>

#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

using namespace std;

int main() {

    // Clear the terminal screen
    system(CLEAR_SCREEN);

    // Print a welcome message
    cout << "Welcome to our command shell!" << endl;
    cout << "Type \"help\" to display a list of commands!" << endl;


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
        int status;
        pid_t pid = fork();
        if (pid == 0) {
            if (command == "tree") {
                execl("./tree", "tree", NULL);
            } else if (command == "list") {
                execl("./list", "list", NULL);
            } else if (command == "path") {
                execl("./path", "path", NULL);
            } else if (command == "help") {
                execl("./help", "help", NULL);
            } else if (command == "exit") {
                // Convert history vector to array of C strings
                char **argv = new char *[history.size() + 1];
                for (size_t i = 0; i < history.size(); ++i) {
                    argv[i] = new char[history[i].size() + 1];
                    strcpy(argv[i], history[i].c_str());
                }
                argv[history.size()] = NULL;

                execv("./exit", argv);

                // Clean up the memory
                for (size_t i = 0; i < history.size(); ++i) {
                    delete[] argv[i];
                }
                delete[] argv;
            } else {
                // If the command is not recognized, print an error message
                cout << "" << command << ": command not found." << endl
                     << "Please try again or run the \"help\" command to see what you can do." << endl;
                exit(1);
            }
        } else if (pid > 0) {
            waitpid(pid, &status, 0);
        } else {
            cerr << "Fork failed" << endl;
            return 1;
        }
    }

    return 0;
}