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
		char* userinfo = getlogin();		// Gets login informatiom from the user (Username and Location)
		char location[20];
		gethostname(location,20);
		cout << "<" << userinfo << "@" << location << ">" << "$ ";
		fgets(&argument,1024,stdin);		// Gets the line of argument from the user
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
			reset:		// The reset label helps look through argument, so we can tokenize
			for(unsigned int i = 0; i < temp.size(); ++i)
			{
				if(temp[i] == ';' && temp.size() > 1 && temp[i+1] == '\0')		// (Semicolon) For single arguments that have a connector at the end
				{
					temp.resize(temp.size() - 1);
					v->push_back(temp);			// Jumps to the end label so argument doesnt get pushed
					temp = ";";	// again
					v->push_back(temp);
					goto end;
				}
				else if(temp[i] == ';' && temp.size() == 1)			// (Semicolon) For when only a semicolon is to be stored 
				{
					v->push_back(temp);
					goto end;
				}
				else if(temp[i] == ';' && temp[i+1] != '\0'){		// (Semicolon) For when there are two commands connected together with
					size_t pos = temp.find(";");		// a semicolon in between or connector is in front of command
					string temp2 = temp.substr(pos + 1);
		
					temp = temp.substr(0, temp.find(";"));
					if(temp.size() != 0)
					{
						v->push_back(temp);
					}
					else
					{
						v->push_back(";");			// Jumps to reset because of arguments after connector needs to be tokenized
					}
					temp = temp2;
					goto reset;
				}
				else if(temp[i] == '|' && temp[i+1] == '|' && temp[i+2] == '\0' && temp.size() > 2)		// (OR) For single arguments that have a
				{		// OR connector at the end
					temp.resize(temp.size() - 2);
					v->push_back(temp);
					v->push_back("||");
					goto end;
				}
				else if(temp[i] == '|' && temp[i+1] == '|' && temp.size() == 2)		// (OR) For when only the OR connector is to be stored
				{
					v->push_back(temp);
					goto end;
				}
				else if(temp[i] == '|' && temp[i+1] == '|' && temp[i+2] != '\0')		// (OR) For when there are two commands connected together
					size_t pos = temp.find("||");		// by the OR connector or connector in front of command
					string temp2 = temp.substr(pos + 2);
				
					temp = temp.substr(0, temp.find("||"));
					if(temp.size() > 0)
					{
						v->push_back(temp);
					}
					else
					{
						v->push_back("||");
					}
			
					temp = temp2;
					goto reset;
				}
				else if(temp[i] == '&' && temp[i+1] == '&' && temp[i+2] == '\0' && temp.size() > 2)		// (AND) For single arguments with an AND
				{		// connector at the end
					temp.resize(temp.size() - 2);
					v->push_back(temp);
					v->push_back("&&");
				}
				else if(temp[i] == '&' && temp[i+1] == '&' && temp.size() == 2)		// (AND) For the single  AND connector 
				{
					v->push_back(temp);
					goto end;
				}
				else if(temp[i] == '&' && temp[i+1] == '&' && temp[i+2] != '\0'){		// (AND) For when two arguments are connected
					size_t pos = temp.find("&&");		// by an AND connector in front of command
					string temp2 = temp.substr(pos + 2);
			
					temp = temp.substr(0, temp.find("&&"));
					if(temp.size() > 0)	
					{
						v->push_back(temp);
					}
					else
					{
						v->push_back("&&");
					}

					temp = temp2;
					goto reset;
				}
					
			}
			v->push_back(temp);		// For when there is just an argument with no connectors attached 
			end:;	
		}
	}
}

bool run(char** runcommand) {
	pid_t PID;
	int waitval;
	if((PID = fork()) < 0) {		// Forks a child process and if fails it exits program
		perror("Forking has failed! ");
		exit(1);
	}
	else if(PID == 0) {			// Executes the command from child process
		if(execvp(*runcommand, runcommand) < 0) {
			perror("Error in execution! ");
			exit(1);
		}
	}
	else {		// Parent waits for completion from child
		while(wait(&waitval) != PID) {};
	}
	if(waitval != 0) {
		return false;
	}	
	return true;
}

// Goes through the vector of tokens and sends each command to the run function
void connectors(vector<string>* v, char** command) {

	int  successful = 0;
	unsigned int i = 0;
	int command_i = 0;
	while(i < v->size()) {
		if(v->at(i) == "exit") {		// Stops running through whole program 
			cout << "Program Exited." << endl;
			exit(0);
		}
		if(v->at(i) == "#") {		// Stops running through vector after seeing the "#" symbol
			command[command_i] = 0;
			successful = run(command);
			break;
		}
		if(v->at(i) == "&&") {		// Executes the next command if the previous one worked
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
		else if(v->at(i) == "||") {	// Executes the next command if the previous one failed
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
		else if(v->at(i) == ";") {	// Executes next command regardless of previous one
			command[command_i] = 0;
			successful = run(command);
			command_i = 0;
			i++;
		}
			
		else {
			command[command_i] = (char*)v->at(i).c_str();	// If no connectors are detected the command is ran
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
	char argument[1024];					// Array of characters that stores the line of command
	vector<string> tokens;					// Vector of strings that holds each command/connector
	char* command[64];						// Holds the current command to execute
	while(1) {
		display(*argument);
		tokenizing(*argument,&tokens);
		connectors(&tokens,command);
		tokens.clear();
	}

return 0;
}
