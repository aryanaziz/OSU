#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define FOREVER 1
#define Max 80        /* maximum length of a line */
#define Max_args 10   /* maximum number of arguments for a command */

/* Declaration of environmental variables */
char PWD[Max];
char PATH[Max];

/* Printing of environmental variables */
void print_env_var (void) {
  printf ("Environmental Variables:\n");
  printf ("   PWD:  %s\n", PWD);
  printf ("   PATH: %s\n", PATH);
}

/* Reading of a user line -- up to the Max length */
void read_line (char line[Max]) {
  int i = 0;
  while ((i < Max) && ((line[i]=getchar()) != '\n'))
    i++;
  /* if reading extends beyond line, truncate line */
  if (i==Max) {
    line[Max-1] = '\0';
    while (getchar() != '\n') ;
  }
  else
    line[i] = '\0';
}

/* copying characters of a string from src string to another */
void string_copy (char str[], char * str_src) {
  int i = 0;
  if (str_src == NULL)
    str[0] = '\0';
  else {
    while ((i < Max-1) && (str_src[i] != '\0')) {
      str[i] = str_src[i];
      i++;
    }
    str[i] = '\0';
  }
}


int main (void) {
  int command_number = 0;
  char command_line [Max];
  char * command_name;
  char * command_args[Max_args];
  pid_t pid;
  int num_args;
  

  /* Initialization */
  printf ("Starting `my-shell'\n");
  string_copy (PWD, getenv("PWD"));
  string_copy (PATH,  getenv("PATH"));

  /* print initial environmental variables */
  printf ("Initial "); 
  print_env_var();

  /* the main shell loop */
  while (FOREVER) { 

    /* print prompt */
    command_number++;
    printf ("my-shell(%d): ", command_number);

    /* read user command */
    read_line (command_line);
    printf ("processing command:  %s\n", command_line);

    /* extract the command name from the command line */    
    command_name = strtok(command_line, " ");
    if (command_name == NULL)
      continue;

    /* check for environment-related command */
    /* relevant commands are
       pev -- print environmental variables
       setd -- set PWD variable
       setp -- set PATH variable
    */
    if (strcmp(command_name, "pev") == 0)
      print_env_var();
    else if (strcmp(command_name, "setp") == 0)
      string_copy (PATH, strtok(NULL, " "));

    /* process non-environment-related commands */
    else {
      /* set up array of command arguments */
      command_args[0] = command_name;
      num_args = 1;
      command_args[num_args] = strtok(NULL, " ");
      while (command_args[num_args] != NULL) {
        num_args++;
        command_args[num_args] = strtok(NULL, " ");
      }
      
      /* apply fork and check for error */
      if ((pid = fork()) < 0)  
     { perror ("error in fork");  
       exit (1);
     }

      if (0 == pid)             
        { /* command processing as child process */
          printf ("creating new process for %s command\n", command_name);

          /* PATH search could go here */


          /* execute desired command */
          execvp (command_name, command_args);
          /* an alternative would be
                execv (full-path-name, command_args);
             where full-path-name gives location and name of file,
             such as /bin/ls
          */
          printf ("error in executing command %s\n", command_name);
          exit (0);
        }

      else { /* my-shell waits for child-command process */
        waitpid (pid, NULL, 0);
      }
    }

  } /* end main loop */  
   
  return 0;

}
