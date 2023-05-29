#include <iostream>
#include <fstream>
#include <unistd.h>

int main() {
    // Get the current working directory
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        // Print the path to the terminal
        std::cout << "Current directory: " << cwd << std::endl;

        // Write the path to a file
        std::ofstream outfile("path.txt");
        if (outfile.is_open()) {
            outfile << cwd << std::endl;
            outfile.close();
            std::cout << "Path written to path.txt" << std::endl;
        }
        else {
            std::cerr << "Unable to write to path.txt" << std::endl;
        }
    }
    else {
        std::cerr << "Unable to get current directory" << std::endl;
    }
    return 0;
}