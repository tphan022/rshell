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
	goto reset;
	while(ptr != NULL) 
	{
		ptr = strtok(NULL, " \n");
		if(ptr != NULL) 
		{
			temp = ptr;
			reset:
			for(int i = 0; i < temp.size(); ++i)
			{
				if(temp[i] == ';' && temp.size() > 1 && temp[i+1] == '\0')
				{
					temp.resize(temp.size() - 1);
					v->push_back(temp);
					temp = ";";
					v->push_back(temp);
					goto end;
				}
				else if(temp[i] == ';' && temp.size() == 1)
				{
					v->push_back(temp);
					goto end;
				}
				else if(temp[i] == ';' && temp[i+1] != '\0')
				{
					size_t pos = temp.find(";");
					string temp2 = temp.substr(pos + 1);
		
					temp = temp.substr(0, temp.find(";"));
					v->push_back(temp);
					v->push_back(";");

					temp = temp2;
					goto reset;
				}
				else if(temp[i] == '|' && temp[i+1] == '|' && temp[i+2] == '\0')
				{
					temp.resize(temp.size() - 2);
					v->push_back(temp);
					v->push_back("||");
					goto end;
				}
				else if(temp[i] == '|' && temp[i+1] == '|' && temp.size() == 2)
				{
					v->push_back(temp);
					goto end;
				}
				else if(temp[i] == '|' && temp[i+1] == '|' && temp[i+2] != '\0')
				{
					size_t pos = temp.find("||");
					string temp2 = temp.substr(pos + 2);
				
					temp = temp.substr(0, temp.find("||"));
					v->push_back(temp);
					v->push_back("||");
			
					temp = temp2;
					goto reset;
				}
				else if(temp[i] == '&' && temp[i+1] == '&' && temp[i+2] == '\0')
				{
					temp.resize(temp.size() - 2);
					v->push_back(temp);
					v->push_back("&&");
				}
				else if(temp[i] == '&' && temp[i+1] == '&' && temp.size() == 2)
				{
					v->push_back(temp);
					goto end;
				}
				else if(temp[i] == '&' && temp[i+1] == '&' && temp[i+2] != '\0')
				{
					size_t pos = temp.find("&&");
					string temp2 = temp.substr(pos + 2);
			
					temp = temp.substr(0, temp.find("&&"));
					v->push_back(temp);
					v->push_back("&&");

					temp = temp2;
					goto reset;
				}
					
			}
			v->push_back(temp);
			end:;	
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
			perror("Error in Execution");
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
