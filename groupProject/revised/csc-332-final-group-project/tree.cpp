#include <iostream>
#include <cstdlib>

int main() {
    //Call "mkdir" to create Dir0 and Dir1
    int dir0_status = system("mkdir -p Dir0");
    int dir1_status = system("mkdir -p Dir0/Dir1");

    //Print to console if both the system calls were successful 
    if (dir0_status == 0) {
        std::cout << "Created Dir0" << std::endl;
    }

    if (dir1_status == 0) {
        std::cout << "Created Dir0/Dir1" << std::endl;
    }

    return 0;
}