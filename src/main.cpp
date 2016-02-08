#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;


// This display function displays the prompt and recieves the user input
void display(char& argument) {
	while(1) {
		char* userinfo = getlogin();
		char location[20];
		gethostname(location,20);
		cout << "<" << userinfo << "@" << location << ">" << "$";
		fgets(&argument,1024,stdin);
		if(argument != '\n') {
			break;
		}
	}
}




int main(void) {
	char argument[1024];
	char* command[64];
	while(1) {
		display(*argument);
	}

return 0;
}
