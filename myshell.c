//Author: Mathew Lister
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
#include <stdbool.h>
#include <fcntl.h>
#include <ctype.h>

//--- Cusom Commands ---//
#include "new_echo.h"
#include "new_cat.h"
//Max input size from user
#define MAX 256

int main(int argc, char *argv[]){
  char input[MAX]; //Array of chars to store text from fgets
  char *token; //Array to hold the current token/command being inspected
  char *temp;
  char **commands;//Array to hold all commands with no white space in order recieved
  char path[100]="PATH=/bin"; //path variable for setpath
  putenv(path); //Initialize path variable to /bin
  int i, redirectIndex, output, fd, commandCount = 0;
  pid_t pid;
  bool redirect = false;

  //Invoking phase:
  //Check for incorrect usage on startup
  if(argc > 2){
    fprintf(stderr, "Command not found\n");
    fprintf(stderr, "my_shell Usage: ./myshell [-h]\n");
  }
  //Check for help
  if(argc == 2){
    // check if second arg is -h
		if(strcmp(argv[1], "-h") == 0){
      //execvp() provides an array of pointers to null-terminated strings that
      //represent the argument list available to the new program. The first argument, by convention,
      //should point to the filename associated with the file being executed.
      //The array of pointers must be terminated by a NULL pointer.
      char *catArgs[3];
      //The strdup() function returns a pointer to a new string which is a
      //duplicate of the string s
			catArgs[0] = strdup("cat");
			catArgs[1] = strdup("myshell_help.txt");
			catArgs[2] = NULL;
			execvp(catArgs[0], catArgs);
			exit(0);
    }
  }

  //Running phase:
  while(true){
    clearerr(stdin);
    //Cear commands array
    for (size_t i=0; i<commandCount; i++){
      free(commands[i]);
      commands[i] = NULL;
    }

    //Read input
    printf("myshell: ");
    //This call to fgets takes a pointer to an array of chars to store input
    //It also takes a number for maximum number of characters to read in
    //Followed by stream where the characters are read from, in this case stdin
    //fgets reads until a terminating newline, EOF or error and returns NULL
    fgets(input, MAX, stdin);

    //Prepare input for inspection
    i = 0;
    //Remove newline from pressing enter
    while(input[i] != '\0'){
      if(input[i] == '\n'){
        input[i] = '\0';
      }
      i++;
    }
    //Cast input to chars
    char *string = (char*)input;
    //If input is just enter
    if(string[0] == '\0'){
      continue;
    }
    //Trim leading whitespace
    //This call to isspace returns a non-zero(true) if char is a white space else return 0(false)
    while(isspace((unsigned char)*string)){
      string++;
    }
    //Parse input to count words
    commandCount = 0; //Keep count of how many commands there are
    for(i = 0; i <= strlen(string); i++){
      //Found space or zero byte (zero byte counts for the first word)
      if(string[i] == ' '|| string[i] == '\0'){
          //Trim trailing whitespace
          //If the next char is also a space we have not found a word yet
          if(isspace(string[i+1])){
            i++;
            //Continue until we find a non whitespace char
            while(isspace(string[i])){
              printf("Found SPACE\n");
              i++;
            }
          }
          //Found a complete word
          commandCount++;
      }
    }
    //This call to malloc taks a size or the size of memory block in bytes to allocate
    //Malloc retunrs a pointer to the allocated memory that we cast into a char pointer
    //Now we have the memory checkedout we can fill it with data
    commands = (char **)malloc(sizeof(char *) * (commandCount + 1));
    temp = strdup(input);
    //break on spaces so we can find individual tokens
    token = strtok(temp, " ");
    i = 0;
    //load seperated tokens into commands
    while(token != NULL){
      if(strcmp(token, ">") == 0){
        redirect = true;
        redirectIndex = i;
      }
      commands[i] = strdup(token);
      token = strtok(NULL, " ");
      i++;
    }
    //Add NULL terminator
    commands[i] = NULL;

    //If need be deal with redirection
    if(redirect == true){
      //'>' must be second to last command with the last being filename
      if(redirectIndex == commandCount-2){
        //Open file with truncate
        fd = open(commands[redirectIndex + 1], O_WRONLY | O_TRUNC | O_CREAT);
        if(fd != -1){
          //Save stdout to the file
          //The dup() system call creates a copy of a file descriptor.
          output = dup(fileno(stdout));
          //Change stdout output to file, then check if success
          //dup2() uses the descriptor number specified by the user
          if(dup2(fd, fileno(stdout)) == -1){
            printf("Could not redirect output\n");
            redirect = false;
          }else{
            //NULL in the place of '>' in commands so we can execute them using new stdout
            commands[redirectIndex] = NULL;
          }
        }
      }else{
        //No file to redirect to, continue to next loop iteration
        printf("Redirection Usage: command > filename\n");
        redirect = false;
        continue;
      }
    }

    //Check for built-in commands
    //exit
    if(strcmp(commands[0], "exit") == 0){
      exit(1);
    }

    //help
    if(strcmp(commands[0], "help") == 0){
      FILE *fp = fopen("myshell_help.txt", "r");
      char tmp;
      if(fp == NULL){
        fprintf(stderr, "Could not find myshell_help.txt\n");
        exit(1);
      }
      else{
        while((tmp = fgetc(fp)) != EOF){
          putchar(tmp);
        }
        fclose(fp);
      }
      continue;
    }

    //pwd
    if(strcmp(commands[0], "pwd") == 0){
      //PATH_MAX defined in limits.h
      char cwd[PATH_MAX];
      if(getcwd(cwd, sizeof(cwd)) != NULL){
        printf("Current working dir: %s\n", cwd);
      }else{
        fprintf(stderr, "Error finding path\n");
      }
      continue;
    }

    //cd
    if(strcmp(commands[0], "cd") == 0){
      if(commandCount > 2){
        fprintf(stderr, "cd Usage: cd [dir]\n");
      }
      else if(commandCount == 1){
        if(chdir(getenv("HOME")) == -1){
          fprintf(stderr, "Invalid Directory\n");
        }
        else{
          char cwd[PATH_MAX];
          // get working path from getcwd
          if(getcwd(cwd, sizeof(cwd)) != NULL){
            printf("Current working dir: %s\n", cwd);
          }
          else{
            fprintf(stderr, "Error finding path\n");
          }
        }
      }else{
        if((chdir(commands[1])) == -1){
          fprintf(stderr, "Invalid Directory %s\n", commands[1]);
        }
        else{
          char cwd[PATH_MAX];
          // get working path from getcwd
          if(getcwd(cwd, sizeof(cwd)) != NULL){
            printf("Current working dir: %s\n", cwd);
          }
          else{
            fprintf(stderr, "Error finding path\n");
          }
        }
      }
      continue;
    }

    //setpath
    if(strcmp(commands[0], "setpath") == 0){
      if(commandCount > 1){
        char path[100]="PATH="; //reset path to be overwritten
        //Add passed in dir's to path
        for(int i = 1; i < commandCount; i++){
          putenv(strcat(path, commands[i]));
        }
        //Print PATH
        char* pPath;
        pPath = getenv("PATH");
        printf("PATH is: %s\n", pPath);
      }
      else{
        fprintf(stderr, "setpath Usage: setpath <dir> [dir] … [dir]\n");
      }
      continue;
    }

    //new_cat
    if(strcmp(commands[0], "new_cat") == 0){
      if(commandCount > 2){
        fprintf(stderr, "Error: Too many arguments\n");
        fprintf(stderr, "new_cat Usage: new_cat [file.txt]\n");
      }
      else if(commandCount == 2){
        new_cat(2, commands[1]);
      }
      else if(commandCount == 1){
        new_cat(1, NULL);
      }
      continue;
    }

    //new_echo
    if(strcmp(commands[0], "new_echo") == 0){
      if(commandCount == 1){
        new_echo(1, commands[0]);
      }
      else{
        for(int i = 1; i < commandCount; i++){
          new_echo(2, commands[i]);
        }
      }
    }
    //else if (program in path -- fork child process and wait for child to finish)
    //fork and call exec for non built-in command
    else{
      pid = fork();
      if(pid < 0){
        //Fork failed
        fprintf(stderr, "Fork filed\n");
        continue;
      }
      //child new process
      else if (pid == 0) {
        //new_tail
        if(strcmp(commands[0], "new_tail") == 0){
          //Using the current set path try to run this command
          execvp("./new_tail", commands);
          //execvp should only return if there was an error
          fprintf(stderr, "Command not found\n");
        }
        //new_wc
        else if(strcmp(commands[0], "new_wc") == 0){
          //Using the current set path try to run this command
          execvp("./new_wc", commands);
          //execvp should only return if there was an error
          fprintf(stderr, "Command not found\n");
        }
        else{
          //Catch all other non builtin commands
          execvp(commands[0], commands);
          //execvp should only return if there was an error
          printf("Invalid Command %s\n", commands[0]);
  				exit(0);
        }
          continue;
        }
        else{
          // parent waits for child to terminate
          wait(NULL);
        }
    }
    //Reset stdout for next iteration
    if(redirect == true){
      //Flush stdout
      fflush(stdout);
      //Close file used to store redirection
      close(fd);
      //Return stdout to its initial file descriptor value
      dup2(output, fileno(stdout));
      //Close output file stream
      close(output);
    }
    redirect = false;
    free(commands);
  }
  return 0;
}
