/* CS344 - Assignment 3 - SmallSh */
/* Author: Aryan Aziz */

//Header Files
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>

//Variables
int quit = 0;
int i;
char line[512];
int background = 0;
int statusCode;
int nullValue = 0;
int bgProcessArray[100];
int numBgProcesses = 0;

//Gets the input from the user and strips out the new line value
void getInput(void) {
	fflush(stdout);
	fflush(stdin);
	printf(": ");
	fflush(stdin);
	if(fgets(line, sizeof(line), stdin) != NULL) { //Makes sure fgets isnt returning null
		char *pos;
		pos=strchr(line, '\n'); //Find the new line value
    	*pos = '\0'; //Change it to end string value
    	if((pos=strchr(line, '&')) != NULL) { //If there is an &
    		*pos = '\0'; //Remove it
    		background = 1; //Keep track that it's a background process
    	}
    	else {
    		background = 0;
    	}
    }
    else { //If fgets is returning null
    	nullValue = 1; //Use this in the main to return
    }
	return;
}

//Runs before each Input and checks if any processes have ended
void checkProcesses(void) {
	int status;
	for(i = 0; i < numBgProcesses; i++) { //Run through the array of process ids
		if(waitpid(bgProcessArray[i], &status, WNOHANG) > 0) {
			if(WIFEXITED(status)) { //If it exited
				printf("Child %d exited with status= %d\n", bgProcessArray[i], WEXITSTATUS(status));
			}
			if(WIFSIGNALED(status)) { //If it was signaled
				printf("Child %d exited with status= %d\n", bgProcessArray[i], WEXITSTATUS(status));
			}
		}
	}
}


int main(int argc, char *argv[], char *envp[]) {
	while(quit == 0) {
		checkProcesses(); //Check the processes
		getInput(); //Grab the input

		if(nullValue == 1) { //If the input was null
			nullValue = 0;
			return 0; //End
		}

		else if(strcmp(line, "exit") == 0) { //If they entered exit
			//printf("\nYou said to exit, exiting\n");
			quit = 1;
			return 0;
		}

		else if(strstr(line, "#")) { //If they entered a comment
			//printf("\nComment, ignoring\n");
			continue;
		}

		else if(strcmp(line, "status") == 0) { //If they entered status
			printf("exited with status: %d\n", statusCode);
			continue;
		}

		else if(strncmp("cd", line, strlen("cd")) == 0) { //If they entered cd
			if(line[2] == ' ') { //If they entered a value to change to
				char cwd[1024];
				getcwd(cwd, sizeof(cwd)); //Grab the current working directory
				char *path = strstr(line, " ");
				//printf("%s\n", path);
				if(path) { //We have to strip out the space from the substring
					path += 1; //Move over 1 spot
					char *value;
					value = malloc(strlen(path));
					memcpy(value, path, strlen(path)); 
					*(value + strlen(path)) = 0;
					sprintf(cwd, "%s/%s", cwd, value); //Create a full current working directory to change to
					free(value); //Clear up memory
				}
				chdir(cwd); //Change it to that directory
			}
			else { //If they just entered cd by itself
				char *home = getenv("HOME"); //Grab the home location
				chdir(home); //Change the cwd to it
			}
		}

		else { //Something not built in (any other command)
			pid_t pid, ppid;
			int status;

			char *commandName;
			char *commandArgs[512];
			int numArgs;
			int redirection = 0;

			commandName = strtok(line, " ");
			if(commandName == NULL) { //Empty line
				continue;
			}

			//Setup Array for execvp
			commandArgs[0] = commandName;
			numArgs = 1;
			commandArgs[numArgs] = strtok(NULL, " "); //Place the next item into the next spot
			while(commandArgs[numArgs] != NULL) { //Keep going until there is no more
				numArgs++;
				commandArgs[numArgs] = strtok(NULL, " ");
			}

			if(background == 1) { //If it's a background process
				if((pid = fork()) < 0) {
					perror("Error while forking");
					exit(1);
				}
				if(pid == 0) { //The child process
					for(i = 0; i < numArgs; i++) {
						if(strcmp(commandArgs[i], "<") == 0) { //Input redirection
							if(access(commandArgs[i+1], R_OK) == -1) { //If we cannot read the file for w/e reason
								printf("cannot open %s for input\n", commandArgs[i+1]);
								redirection = 1;
							}
							else { //If the file can be read
								int fd = open(commandArgs[i+1], O_RDONLY, 0);
								dup2(fd, STDIN_FILENO);
								close(fd);
								redirection = 1;
								execvp(commandName, &commandName); //Execute the command 
							}
						}
						if(strcmp(commandArgs[i], ">") == 0) { //Output redirection
							int fd = creat(commandArgs[i+1], 0644); //Create the file
							dup2(fd, STDOUT_FILENO);
							close(fd);
							redirection = 1;
							execvp(commandName, &commandName); //Execute the command
						}
					}
					if(redirection == 0) { //If no input or output redirection
						execvp(commandName, commandArgs); //Execute the command
					}
					printf("%s no such file or directory\n", commandName); //Only gets here if there is an error
					exit(1);
				}
				else { //Parent process
					int status;
					int process;
					printf("background pid is %d\n", pid);
					bgProcessArray[numBgProcesses] = pid; //Keep track of background processes
					numBgProcesses++;
					process = waitpid(pid, &status, WNOHANG);
					continue;
				}
			}
			else { //If it's a foreground process
				if((pid = fork()) < 0) {
					perror("Error while forking");
					exit(1);
				}
				if(pid == 0) { //Child process
					for(i = 0; i < numArgs; i++) {
						if(strcmp(commandArgs[i], "<") == 0) { //Input redirection
							if(access(commandArgs[i+1], R_OK) == -1) { //If we cannot read the file for w/e reason
								printf("cannot open %s for input\n", commandArgs[i+1]);
								redirection = 1;
							}
							else { //If the file can be read
								int fd = open(commandArgs[i+1], O_RDONLY, 0);
								dup2(fd, STDIN_FILENO);
								close(fd);
								redirection = 1;
								execvp(commandName, &commandName); //Execute the command
							}
						}
						if(strcmp(commandArgs[i], ">") == 0) { //Output redirection
							int fd = creat(commandArgs[i+1], 0644); //Create the file
							dup2(fd, STDOUT_FILENO);
							close(fd);
							redirection = 1;
							execvp(commandName, &commandName); //Execute the command
						}
					}
					if(redirection == 0) { //If no redirection
						execvp(commandName, commandArgs); //Execute the command
					}
					printf("%s no such file or directory\n", commandName); //Only gets here if there is an error
					exit(0);
				}
				else { //Parent process
					int status;
					waitpid(pid, &status, 0); //Wait for the process
					if(WIFEXITED(status)) {
						statusCode = WEXITSTATUS(status);
					}
				}
			}
		}
		signal(SIGINT, SIG_IGN); //Capture the sigint and ignore it. 
	}
	return 0;
}