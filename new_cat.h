#include <stdio.h>

//argc = number of arguments passed in
//argv = list of arguments passed in
void new_cat(int argc, char *argv){
  const int MAX = 256; //The maximum number of characters to be read including EOF

  //Edge case 1 error handling
  //If the user passes in more than one file name - abort
  if(argc > 2){
    fprintf(stderr, "Error: Too many arguments\n");
  }

  //Edge case 2 error handling
  //If user does not pass in a file name
  //Print out what they type until they enter 'CTRL + D'
  if(argc < 2){
    char input[MAX]; //Array of chars to store input from user

    //This call to fgets takes a pointer to an array of chars to store input
    //It also takes a number for maximum number of characters to read in
    //Followed by stream where the characters are read from, in this case stdin
    //fgets reads until a terminating newline, EOF or error and returns NULL
    while(fgets(input, MAX, stdin)){
      if(feof(stdin)){
        printf("\n");
      } //The user has entered CTRL+D/
      puts(input);
    }
    fclose(stdin);
  }

  //Base case
  //If two arguments are passed in try to open the file
  //If error opening the file - abort
  //If can be opened, print contents to stdout
  else{
    //This is the file pointer set to a call with fopen
    //fopen takes a file name that we get from the second argument given when program is started
    //fopen is also to to read only mode with "r"
    FILE *file = fopen(argv, "r");
    char output[MAX]; //Array of chars to store text from file

    //Check if file exists
    if(file == NULL){
      fprintf(stderr, "Error: Cannot open file\n");
    }
    else{
      //This loop will read the file line by line until it reaches EOF/NULL
      //This call to fgets takes the array of stored text from the file
      //It also takes the max size of characters to read in
      //Followed by the stream where the characters are read from, in this case the file
      while(fgets(output, sizeof(output), file) != NULL){
        printf("%s", output);
      }
      //Close the file
      fclose(file);
    }
  }
}
