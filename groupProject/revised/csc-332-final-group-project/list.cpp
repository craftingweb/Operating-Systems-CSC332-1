#include<iostream>
#include<dirent.h>
#include<sys/types.h>
#include<stdlib.h>
#include<fstream>
#include<conio.h>

using namespace std;

int main(void) {

	clrscr();  //clears the terminal scrren

	DIR* dr;
	struct dirent* en;
	dr = opendir("."); // opens the current directory
	ofstream file;
	file.open("list.txt"); //creates file named "list.txt"
	if (dr) {
		while ((en = readdir(dr)) != NULL) {
			cout << " \n" << en->d_name; //prints all contents of directory
			file << " \n" << en->d_name; //writes contents of directory into text file
		}
		file.close();//closes text file
		closedir(dr); //closes current directory
	}
	return(0);
}