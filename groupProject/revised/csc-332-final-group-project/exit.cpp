#include <iostream>
#include <cstdlib>
#include <vector>

int main(int argc, char* argv[]) {
    // Print the history of commands
    std::cout << "\nHistory of commands:" << std::endl;
    for (int i = 1; i < argc; i++) std::cout << argv[i] << std::endl;
    std::cout << std::endl;

    // Print a detailed list of all the content of the current directory aka. like "ls -l"
    std::cout << "\nCurrent directory content: " << std::endl;
    system("ls -l");
    std::cout << std::endl;

    // Wait for the user to acknowledge and exit the shell
    std::cout << "Press RETURN key in order to exit the shell" << std::endl;
    while (true) {
        if (std::cin.get() == '\n') { // waiting for return key to be press
            std::cout << "Have a nice day!!!\n" << std::endl;
            break;
        }
        std::cin.ignore(); // clear buffer
    }
    return 0;
}