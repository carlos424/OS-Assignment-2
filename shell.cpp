#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

#define MAX_LINE 80 /*The max length command*/

int main(void)
{
	char *args[MAX_LINE/2 +1]; /*command line arguments */
	int should_run = 1; /* flag to determine when to exit program */
	vector<string> stack;
	stackCount = 0;
	while (should_run)
	{
		printf("osh>");
		fflush(stdout);
		string input;
		getline(cin, input);
		stack.push_back(input);
		int stackCount++;
		
		if(stackCount > 10){
			stack.erase(stack.begin());
		}
		
		// Split String input
		string com = "";
		int count = 0;
		bool hasAmper = false;
		for(int i = 0; i < input.length(); i++)
		{
			/* if else block for commands with multiple phrases such as ls -a */
			if(input[i] == ' ') 
			{
				char* writable = new char[com.size() + 1];
				copy(com.begin(), com.end(), writable);
				writable[com.size()] = '\0';
				args[count] = writable;
				delete[] writable;
				com = "";
				count++;
			}
			else 
			{
				com += input[i];
			}
			
			/* if block if we have a single word command such as ls */
			if(i == input.length() -1) 
			{
				char* writable = new char[com.size() + 1];
                copy(com.begin(), com.end(), writable);
                writable[com.size()] = '\0';
                args[count] = writable;
				delete[] writable;
			}
			
			/* set flag for amper*/
			if(input[i] == '&') 
			{
				hasAmper = true;
			}
			
			/* show history */
			if(com == "history") 
			{
				for(int i = 0; i < 10; i++) 
				{
					cout << stack[i] << endl;

				}
			}
			
			/*exit program if we see exit input */
			if(com == "exit") 
			{
				should_run = 0;
			}
			

			
			/* do last command if !! */
			if(com == "!!")
			{
				input = stack[stack.size()];
				com = "";
				count = 0;
				hasAmper = false;
				for(int i = 0; i < input.length(); i++)
				{
					/* if else block for commands with multiple phrases such as ls -a */
					if(input[i] == ' ') 
					{
						char* writable = new char[com.size() + 1];
						copy(com.begin(), com.end(), writable);
						writable[com.size()] = '\0';
						args[count] = writable;
						delete[] writable;
						com = "";
						count++;
					}
					else 
					{
						com += input[i];
					}
					
					/* if block if we have a single word command such as ls */
					if(i == input.length() -1) 
					{
						char* writable = new char[com.size() + 1];
						copy(com.begin(), com.end(), writable);
						writable[com.size()] = '\0';
						args[count] = writable;
						delete[] writable;
					}
					
					/* set flag for amper*/
					if(input[i] == '&') 
					{
						hasAmper = true;
					}
					
					/* show history */
					if(com == "history") 
					{
						for(int i = 0; i < 10; i++) 
						{
							cout << stack[i] << endl;

						}
					}
				}
			
		}
		
		/* used to test and show user input  
		
		for(int i = 0; i < count; i++) {
			cout << args[i] << endl;
		}		
		*/


		/*
		after reading user input, the steps include:
		1 - fork a child process using fork()
		2 - the child process will invoke execvp()
		3 - if command didn't included &, parent wil linvoke wait()
		*/
		
		/*	Step  1*/
		pid_t pid; /* fork a child process */
		pid = fork();
		
		
		if( pid == 0)/* do something if child */
		{
			execvp(args[0],args);
		}
		/*	Step  2*/
		
		
		/*	Step  3*/
		else /* parent process */
		{
			if(!hasAmper) /* test if parent didn't include & */
			{
				
				wait(NULL);
			}
		}
	}
	
	return 0;
}
