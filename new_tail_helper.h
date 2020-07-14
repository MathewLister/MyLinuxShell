#include<string.h>
#include<stdlib.h>
#include<stdio.h>

//Function that takes in a pointer array of type char
//Checks if each char in the string passes an num only validation
//Validation is done with isdigit
//The function returns 0 if the string contains non-numerical characters
//The function returns 1 if the string only contains numbers 0-9
//Note: no negative numbers or decmals will return 1
int digits_only(const char *string)
{
    while (*string) { //while the pointer != '\0' -- zero byte//
        //This call to isdigit will check if(*string<'0' || *string>'9')
        if (isdigit(*string++) == 0){ //*string++ uses pointer arithmatic to incremeant the pointer
                                      //Could also be described as walking the pointer through the string
          return 0;
        }
    }
    return 1;
}

//Function that takes in a file name and a length (n)
//The function does the following:
//Count number of lines --> numLines;
//Create char *lines[numLines]
//Read line by line --> push to []
//Pop line by line n or 'length' times
  //If length < number of lines --> print entire file
void readLastNLinesFromFile(char *file, int length)
{
  const int MAX = 256; //The maximum number of characters to be read including EOF
  char output[MAX]; //Array of chars to store text from file
  int numLines = 0, i = 0; //The number of lines in the file
  FILE *fileNameCount = fopen(file, "r"); //Temp filestream to count lines we will close this soon
  FILE *fileName = fopen(file, "r"); //File stream to read and store from

  if(fileNameCount == NULL){
    fprintf(stderr, "Error: Cannot open file\n");
  }
  else{  //READ
    //This loop will read the file line by line until it reaches EOF/NULL
    //This call to fgets takes the array of stored text from the file
    //It also takes the max size of characters to read in
    //Followed by the stream where the characters are read from, in this case the file
    while(fgets(output, sizeof(output), fileNameCount) != NULL){
      numLines++;
    }
    fclose(fileNameCount);

    char *lines[numLines]; //Array of chars to store all lines in the file
    while(fgets(output, sizeof(output), fileName) != NULL){
      //This call to malloc taks a size or the size of memory block in bytes to allocate
      //Malloc retunrs a pointer to the allocated memory that we cast into a char pointer
      //Now we have the memory checkedout we can fill it with data
      lines[i] = (char*) malloc(MAX);
      //This call to strcpy take a destination and a source
      strcpy(lines[i], output);
      i++;
    }
    fclose(fileName);

    //If there is less lines than length just print the entire file
    if(numLines < length){
      for(int i = 0; i < numLines; i++){
        printf("%s", lines[i]);
      }
    }
    else{
      //Pull from the array and print
      //Position i at the top of where we should start reading and read until the end
      for(i = numLines - length; i < numLines; i++){
        printf("%s", lines[i]);
      }
    }
  }
}


void readLastNLinesFromConsole(int length)
{
  const int MAX = 256; //The maximum number of characters to be read including EOF
  char output[MAX]; //Array of chars to store text from fgets
  char *lines[MAX]; //Array of chars to store all lines in the file //Array of chars to store input from user
  int lineCount = 0; //Keep track of how many lines the user enters

  //This call to fgets takes a pointer to an array of chars to store input
  //It also takes a number for maximum number of characters to read in
  //Followed by stream where the characters are read from, in this case stdin
  //fgets reads until a terminating newline, EOF or error and returns NULL
  while(fgets(output, MAX, stdin)){
    //This call to malloc taks a size or the size of memory block in bytes to allocate
    //Malloc retunrs a pointer to the allocated memory that we cast into a char pointer
    //Now we have the memory checkedout we can fill it with data
    lines[lineCount] = (char*) malloc(MAX);
    //This call to strcpy take a destination and a source
    strcpy(lines[lineCount], output);
    lineCount++;
    if(feof(stdin) || lineCount == MAX){ //The user has entered CTRL+D/EOF or entered the max number of lines
      printf("\n");
      fclose(stdin);
      break;
    }
  }
  //If there is less lines than length just print the entire input
  if(lineCount < length){
    for(int i = 0; i < lineCount; i++){
      printf("%s", lines[i]);
    }
  }
  else{
    //Position i at the top of where we should start reading and read until the end
    for(int i = lineCount - length; i < lineCount; i++){
      printf("%s", lines[i]);
    }
    printf("\n");
  }
}
