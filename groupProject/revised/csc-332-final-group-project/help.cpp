#include <iostream>

int main() {
    std::cout << "Below are the commands you can use:" << std::endl;
    std::cout << "tree\t->\tCreates a directory and call it Dir0, and one empty directory, called Dir1, inside it." << std::endl;
    std::cout << "list\t->\tClear the terminal screen and print a detailed list of all content of the current directory (like ls -l) to the terminal and a file called tree.txt after creating it." << std::endl;
    std::cout << "path\t->\tPrint the current directory's path to the terminal and to a file called path.txt after creating it." << std::endl;
    std::cout << "exit\t->\tPrints a list of the last few commands to the terminal, a detailed list of all content of the current directory (like ls -l) and then exits the shell." << std::endl;
    std::cout << std::endl;
    return 0;
}