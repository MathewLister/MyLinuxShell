#include<string.h>
#include<stdlib.h>
#include<stdio.h>


void numLines(char *file)
{
  const int MAX = 256; //The maximum number of characters to be read including EOF
  char output[MAX]; //Array of chars to store text from file
  int numLines = 0, numWords = 0;
  char ch;
  FILE *fileName = fopen(file, "r"); //File stream to read and store from
  FILE *fileChars = fopen(file, "r"); //Reusing the file stream is giving me unpredictable results
  if(fileName == NULL){
    fprintf(stderr, "Error: Cannot open file\n");
  }
  else{
    //Count lines
    //This loop will read the file line by line until it reaches EOF/NULL
    //This call to fgets takes the array of stored text from the file
    //It also takes the max size of characters to read in
    //Followed by the stream where the characters are read from, in this case the file
    while(fgets(output, sizeof(output), fileName) != NULL){
      numLines++;
    }
    fclose(fileName);
    //Cound words
    //This call to fgetc takes a file stream and returns thr char read
    //Checking if the word is a space, tab, newline or zero byte signifies that we have reached the end of a word
    ch = fgetc(fileChars);
    while(ch != EOF){
      if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0'){
        numWords++;
      }
      ch = fgetc(fileChars);
    }
    printf("%d %d %s\n",numWords, numLines, file);
    fclose(fileChars);
  }
}

void numChars(char *file)
{
  int numChars = 0, numWords = 0;
  char ch;
  FILE *fileName = fopen(file, "r"); //File stream to read and store from
  if(fileName == NULL){
    fprintf(stderr, "Error: Cannot open file\n");
  }
  else{
    //Count words
    //This call to fgetc takes a file stream and returns thr char read
    //Checking if the word is a space, tab, newline or zero byte signifies that we have reached the end of a word
    ch = fgetc(fileName);
    while(ch != EOF){
      numChars++;
      if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0'){
        numWords++;
      }
      ch = fgetc(fileName);
    }
    printf("%d %d %s\n",numWords, numChars, file);
    fclose(fileName);
  }
}

void readFile(char *file)
{
  int numWords = 0;
  char ch;
  FILE *fileName = fopen(file, "r"); //File stream to read and store from
  if(fileName == NULL){
    fprintf(stderr, "Error: Cannot open file\n");
  }
  else{
    //Count words
    //This call to fgetc takes a file stream and returns thr char read
    //Checking if the word is a space, tab, newline or zero byte signifies that we have reached the end of a word
    ch = fgetc(fileName);
    while(ch != EOF){
      if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0'){
        numWords++;
      }
      ch = fgetc(fileName);
    }
    printf("%d %s\n",numWords, file);
    fclose(fileName);
  }
}


void consoleLines()
{
  const int MAX = 256; //The maximum number of characters to be read including EOF
  char output[MAX]; //Array of chars to store text from fgets
  int numLines = 0, numWords = 0;
  char *ch;

  while(fgets(output, MAX, stdin)){
    //Count lines
    numLines++;

    //Count words
    //If the line only contains \n then there is no words here
    if(output[0] == '\n'){
      continue;
    }
    //Char pointer is set to right before the array
    ch = output -1;
    //This call to strchr takes a c string to be read and a charater to search for
    //Returns a pointer to the first occurrence of the character or NULL
    //While strchr does not return NULL
    while (ch = strchr(ch+1, ' ')) {
      //If not NULL then we found a space --> meaning we found the end of a word
      numWords++;
    }
    //Count the word before the \0 or zero byte
    numWords++;
    if(feof(stdin)){ //The user has entered CTRL+D/EOF
      printf("\n");
      break;
    }
  }
  printf("%d %d\n", numWords, numLines);
}

void consoleChars()
{
  const int MAX = 256; //The maximum number of characters to be read including EOF
  char output[MAX]; //Array of chars to store text from fgets --> initalized to NUL
  int numChars = 0, numWords = 0;
  char *ch;

  while(fgets(output, MAX, stdin)){
    //Count words and chars
    //If the line only contains \n then there is no words here
    if(output[0] == '\n'){
      continue;
    }
    //Char pointer is set to right before the array
    ch = output -1;
    //This call to strchr takes a c string to be read and a charater to search for
    //Returns a pointer to the first occurrence of the character or NULL
    //While strchr does not return NULL
    while (ch = strchr(ch+1, ' ')) {
      //If not NULL then we found a space --> meaning we found the end of a word
      numWords++;
    }
    //Count the word before the \0 or zero byte
    numWords++;
    if(feof(stdin)){ //The user has entered CTRL+D/EOF
      printf("\n");
      break;
    }
  }
  for(int i = 0; i < MAX; i++){
    //Incase the user did not fill up the input buffer
    if(output[i] == EOF){
      break;
    }
    numChars++;
  }
  printf("%d %d\n", numWords, numChars);
}
