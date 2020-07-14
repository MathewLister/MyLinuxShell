#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> //Standard Library that declares int isdigit(int)
#include <string.h>
#include "new_tail_helper.h"

//argc = number of arguments passed in
//argv = list of arguments passed in
int main(int argc, char *argv[]){
  int n = 5;
  char *flag[1] = {"-n"};
  //If user passes a file -> print last n lines
  //If uses passes in four arguments, we need to find -n and the file
  //-n can only be in argument position two or three
  //If no n -> default = 5
  if(argc == 4){
    //This call to strcmp will return 0 if both strings passed in are equal
    if(strcmp(argv[1], flag[0]) == 0){
      //Check if number
      char *temp = argv[2];
      if(digits_only(temp) == 1){
        if(isdigit(*temp) != 0){
          n = atoi(temp);
          if(n != 0){
            readLastNLinesFromFile(argv[3], n);
          }
        }
      }
    }
    if(strcmp(argv[2], flag[0]) == 0) {
      //Check if number
      char *temp = argv[3];
      if(digits_only(temp) == 1){
        if(isdigit(*temp) != 0){
          n = atoi(temp);
          if(n != 0){
            readLastNLinesFromFile(argv[1], n);
          }
        }
      }
    }
  }

  //Else read from stdin until EOF -> print last n lines types or 5
  //If the user passes in three arguments, we might just have ./new_tail -n N
  if(argc == 3){
    if(argv[1] = "-n"){
      //Check if number
      char *temp = argv[2];
      if(digits_only(temp) == 1){
        if(isdigit(*temp) != 0){
          n = atoi(temp);
          if(n != 0){
            //READ FROM INPUT
            readLastNLinesFromConsole(n);
          }
        }
      }
    }
  }
  //If the user passes in two arguments, we might have ./new_tail file.txt
  if(argc == 2){
    readLastNLinesFromFile(argv[1], n);
  }
  return 0;
}
