#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

using namespace std;


// This display function displays the prompt and recieves the user input
void display(char& argument) {
	while(1) {
		char* userinfo = getlogin(); // Gets login informatiom from the user (Username and Location)
		char location[20];
		gethostname(location,20);
		cout << "<" << userinfo << "@" << location << ">" << " $ ";
		fgets(&argument,1024,stdin); // Gets the line of argument from the user
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
				if(temp[i] == ';' && temp.size() > 1 // For single arguments w/ semicolon at the end
					&& temp[i+1] == '\0')
				{
					temp.resize(temp.size() - 1);
					v->push_back(temp); // Jumps to the end label so argument doesnt get pushed twice
					temp = ";";
					v->push_back(temp);
					goto end;
				}
				else if(temp[i] == ';' && temp.size() == 1) // (Semicolon) For when only a semicolon is to be stored 
				{
					v->push_back(temp);
					goto end;
				}
				else if(temp[i] == ';' && temp[i+1] != '\0'){ // (Semicolon) For when there are two commands connected together with
					size_t pos = temp.find(";");              // a semicolon in between or connector is in front of command
					string temp2 = temp.substr(pos + 1);
		
					temp = temp.substr(0, temp.find(";"));
					if(temp.size() != 0)
					{
						v->push_back(temp);
						v->push_back(";");
					}
					else
					{
						v->push_back(";"); // Jumps to reset because of arguments after connector needs to be tokenized
					}
					temp = temp2;
					goto reset;
				}
				else if(temp[i] == '|' && temp[i+1] == '|' && temp[i+2] == '\0'		
					 && temp.size() > 2) // (OR) For single arguments that have a OR connector at the end
				{
					temp.resize(temp.size() - 2);
					v->push_back(temp);
					v->push_back("||");
					goto end;
				}
				else if(temp[i] == '|' && temp[i+1] == '|' 
					&& temp.size() == 2) // (OR) For when only the OR connector is to be stored
				{
					v->push_back(temp);
					goto end;
				}
				else if(temp[i] == '|' && temp[i+1] == '|' && temp[i+2] != '\0'){ // (OR) For when there are two commands connected together
					size_t pos = temp.find("||");                                 // by the OR connector or connector in front of command
					string temp2 = temp.substr(pos + 2);
				
					temp = temp.substr(0, temp.find("||"));
					if(temp.size() > 0)
					{
						v->push_back(temp);
						v->push_back("||");
					}
					else
					{
						v->push_back("||");
					}
			
					temp = temp2;
					goto reset;
				}
				else if(temp[i] == '&' && temp[i+1] == '&' && temp[i+2] == '\0' && temp.size() > 2) // (AND) For single arguments with an AND
				{		                                                                            // connector at the end
					temp.resize(temp.size() - 2);
					v->push_back(temp);
					v->push_back("&&");
				}
				else if(temp[i] == '&' && temp[i+1] == '&' && temp.size() == 2) // (AND) For the single  AND connector 
				{
					v->push_back(temp);
					goto end;
				}
				else if(temp[i] == '&' && temp[i+1] == '&' && temp[i+2] != '\0'){ // (AND) For when two arguments are connected
					size_t pos = temp.find("&&");                                 // by an AND connector in front of command
					string temp2 = temp.substr(pos + 2);
			
					temp = temp.substr(0, temp.find("&&"));
					if(temp.size() > 0)	
					{
						v->push_back(temp);
						v->push_back("&&");
					}
					else
					{
						v->push_back("&&");
					}

					temp = temp2;
					goto reset;
				}
				else if(temp[i] == '(' && temp.size() == 1) // Detects single starting bracket and pushes into vector
				{
					v->push_back(temp);
					goto end;
				}
				else if(temp[i] == '(' && temp.size() > 1 && temp[i+1] == '\0') // Detects command with starting bracket at end
				{
					temp.resize(temp.size() - 1);
					v->push_back(temp);
					v->push_back("(");
					goto end;
				}
				else if(temp[i] == '(' && temp[i+1] != '\0') // Detects command with starting bracket in the middle or in front
				{
					size_t pos = temp.find("(");
					string temp2 = temp.substr(pos + 1);
					
					temp = temp.substr(0, temp.find("("));
					if(temp.size() != 0)
					{
						v->push_back(temp);
						v->push_back("(");
					}
					else
					{
						v->push_back("(");
					}
					temp = temp2;
					goto reset;
				}
				else if(temp[i] == ')' && temp.size() == 1) // Detects single ending bracket and pushed into vector
				{
					v->push_back(temp);
					goto end;
				}
				else if(temp[i] == ')' && temp.size() > 1 && // Detects command with ending bracket at the end
					temp[i+1] == '\0')
				{
					temp.resize(temp.size() - 1);
					v->push_back(temp);
					v->push_back(")");
					goto end;
				}
				else if(temp[i] == ')' && temp[i+1] != '\0'){ // Detects command with ending bracket in the middle or in front
					size_t pos = temp.find(")");
					string temp2 = temp.substr(pos + 1);
		
					temp = temp.substr(0, temp.find(")"));
					if(temp.size() != 0)
					{
						v->push_back(temp);
						v->push_back(")");
					}
					else
					{
						v->push_back(")");
					}
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
	int waitval;
	if((PID = fork()) < 0) { // Forks a child process and if fails it exits program
		perror("Forking has failed! ");
		exit(1);
	}
	else if(PID == 0) { // Executes the command from child process
		if(execvp(*runcommand, runcommand) < 0) {
			perror("Error in execution! ");
			exit(1);
		}
	}
	else { // Parent waits for completion from child
		while(wait(&waitval) != PID) {};
	}
	if(waitval != 0) {
		return false;
	}	
	return true;
}

bool testcommand(int selector, string dir) {
	bool check = false;
	struct stat buf;
	//This is the -e and nothing selected case
	if(selector == 0) {
		//The stat system call checks to see whether the file/directory exists
		//and returns a boolean value of whether it exists.
		check = (stat(dir.c_str(), &buf) == 0);
		if(check) {
			cout << "(True)" << endl;
			return true;
		}
		else {
			cout << "(False)" << endl;
			return false;
		}
	}
	//This checks to see if the target is a regular file.
	else if(selector == 1) {
		check = (stat(dir.c_str(), &buf) == 0);
		bool check2 = false;
		if(check) {
			//This is a second check using stat's S_ISREG macro to check if
			//the file/directory checked was a regular file.
			check2 = S_ISREG(buf.st_mode);
			//If the case was true then this returns true.
			if(check2) {
				cout << "(True)" << endl;
				return true;
			}
			else {
				cout << "(False)" << endl;
				return false;
			}
		}
		else {
			cout << "(False)" << endl;
			return false;
		}
	}
	//This checks to see if the target is a directory.
	else if(selector == 2) {
		check = (stat(dir.c_str(), &buf) == 0);
		bool check2 = false;
		if(check) {
			check2 = S_ISREG(buf.st_mode);
			//If this check is false then it is most likely 
			// a directory (not a regular file).
			if(!check2) {
				cout << "(True)" << endl;
				return true;
			}
			else {
				cout << "(False)" << endl;
				return false;
			}
		}
		else {
			cout << "(False)" << endl;
			return false;
		}
	}
	//This case should never happen.
	else{
		perror("invalid test command case");
		exit(1);
	}
	return false;
}

// Goes through the vector of tokens and sends each command to the run function
bool connectors(vector<string>* v, char** command) {

	int  successful = 0;
	unsigned int i = 0;
	int command_i = 0;
	bool parencheck = false;
	bool testcase = false;
	while(i < v->size()) {
		if(v->at(i) == "exit") { // Stops running through whole program 
			cout << "Program Exited." << endl;
			exit(0);
		}
		if(v->at(i) == "#") { // Stops running through vector after seeing the "#" symbol
			if(parencheck == true)
			{
				parencheck = false;
				break;
			}
			command[command_i] = 0;
			successful = run(command);
			break;
		}
		// This is the new if statement for checking if this is the test command
		if(v->at(i) == "test" || v->at(i) == "[") {
			string testcode;
			i++;
			testcode = v->at(i);
			//These will check is the line is a flag, if it is not
			// then will set -e as the default.
			if(testcode == "-e") {
				i++;
				testcode = v->at(i);
				//This calls the test command function which returns a boolean value.
				successful = testcommand(0, testcode);
			}
			else if(testcode == "-f") {
				i++;
				testcode = v->at(i);
				successful = testcommand(1, testcode);
			}
			else if(testcode == "-d") {
				i++;
				testcode = v->at(i);
				successful = testcommand(2, testcode);
			}
			else {
				successful = testcommand(0, testcode);
			}
			i++;
			//These checks to see if this command is the last command in the order,
			// if it is, then break out of the loop before out-of-range happens.
			if(i >= v->size()) {
				break;
			}
			else if(v->at(i) == "]") {
				i++;
				if(i >= v->size()) {
					break;
				}

			}
			//The testcase flag has checks throughout the entire loop and will skip
			// the usual implimentation accordingly because the test command
			// was used. 
			testcase = true;
			command_i = 0;
		}

		if(v->at(i) == "&&") { // Executes the next command if the previous one worked
			if(!testcase) {
				if(parencheck == false)
				{
					command[command_i] = 0;
					successful = run(command);
				}
				else
				{
					parencheck = false;
				}
			}
			else{
				testcase = false;
			}
			if(!successful) {
				break;
			}
			else {
				command_i = 0;
				i++;
			}

		}
		else if(v->at(i) == "||") {	// Executes the next command if the previous one failed
			if(!testcase) {
				if(parencheck == false)
				{
					command[command_i] = 0;
					successful = run(command);
				}
				else
				{
					parencheck = false;
				}
			}
			else{
				testcase = false;
			}
			if(!successful) {
				command_i = 0;
				i++;
			}
			else {
				//break; PREVIOUS CODE
				while(i < v->size()) {
					if(v->at(i) == "&&") {
						i++;
						command_i = 0;
						break;
					}
					else if(v->at(i) == ";") {
						i++;
						command_i = 0;
						break;
					}
					i++;
				}
				if(i >= v->size()) {
					break;
				}
			}
		}
		else if(v->at(i) == ";") { // Executes next command regardless of previous one
			if(!testcase) {
				//check to see if semicolon works.
				if(parencheck == false)
				{
					command[command_i] = 0;
					successful = run(command);
				}
				else
				{
					parencheck = false;
				}
			}
			else{
				testcase = false;
			}
			command_i = 0;
			i++;
		}
		else if(v->at(i) == "(") // Pushes commands into the new vector and recursively calls to find whether true or false
		{
			vector<string> paren;
			paren.clear();
			parencheck = true;
			++i;
			while(v->at(i) != ")")
			{
				paren.push_back(v->at(i));
				++i;
			}
			successful = connectors(& paren, command);
			command_i = 0;
			++i;
		}
		else {
			// added checks throughout the function to see if tesrcases were used
			if(!testcase) {
				command[command_i] = (char*)v->at(i).c_str(); 
				// If no connectors are detected the command is ran
				command[command_i+1] = 0;
				command_i++;
				i++;
				if(i >= v->size()) {
					successful = run(command);
					break;
				}
			}
			else { 
				testcase = false;
				break;
			}
		}
	}
	if(successful) // Returns either true or false depending on whether the commands executred correctly
	{
		return true;
	}
	else
	{
		return false;
	}
		
}

int main(void) {
	char argument[1024]; // Array of characters that stores the line of command
	vector<string> tokens; // Vector of strings that holds each command/connector
	char* command[64]; // Holds the current command to execute
	while(1) {
		display(*argument);
		tokenizing(*argument,&tokens);
		connectors(&tokens,command);
		tokens.clear();
	}

return 0;
}
