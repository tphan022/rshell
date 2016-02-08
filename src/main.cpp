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

// This function turns the array of input characters into separate tokens(strings)
void tokenizing(char& argument, vector<string>* v) {
	char* ptr;
	ptr = strtok(&argument, " \n");
	string temp(ptr);
	v->push_back(temp);
	while(ptr != NULL) {
		
		ptr = strtok(NULL, " \n");
		if(ptr != NULL) {
			string temp2(ptr);
			v->push_back(temp2);
		}
	}
}

bool run(char** runcommand) {
	pid_t PID;
	int s;
	if((PID = fork()) < 0) {
		cout << "Error, forking failed" << endl;
		exit(1);
	}
	else if(PID == 0) {
		if(execvp(*runcommand, runcommand) < 0) {
			cout << "Error: execution Error" << endl;
			exit(1);
		}
	}
	else {
		while(wait(&s) != PID) {};
	}
	if(s != 0) {
		return false;
	}	
	return true;
}

void connectors(vector<string>* v, char** command) {

	int  successful = 0;
	unsigned int i = 0;
	int command_i = 0;
	while(i < v->size()) {
		if(v->at(i) == "exit") {
			cout << "Program Exited." << endl;
			exit(0);
		}
		if(v->at(i) == "#") {
			command[command_i] = 0;
			successful = run(command);
			break;
		}
		if(v->at(i) == "&&") {
			command[command_i] = 0;
			successful = run(command);
			if(!successful) {
				break;
			}
			else {
				command_i = 0;
				i++;
			}

		}
		else if(v->at(i) == "||") {
			command[command_i] = 0;
			successful = run(command);
			if(!successful) {
				command_i = 0;
				i++;
			}
			else {
				break;
			}
		}
		//else if(v->at(i).at(v->at(i).size() - 1) == ";") {
		//	string temp = v->at(i).substr(0,v->at(i).size()-1);
		//	command[command_i] = (char*)temp.c_str();
		//	command[command_i + 1] = 0;
		//	successful = run(command);
		//	i++;
		//	command_i = 0;
		//}
			
		else {
			command[command_i] = (char*)v->at(i).c_str();
			command[command_i+1] = 0;
			command_i++;
			i++;
			if(i >= v->size()) {
				successful = run(command);
				break;
			}
		}
	}
		
}

int main(void) {
	char argument[1024];
	vector<string> tokens;
	char* command[64];
	while(1) {
		display(*argument);
		tokenizing(*argument,&tokens);
		connectors(&tokens,command);
		tokens.clear();
	}

return 0;
}
