#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "new_wc_helper.h"

//argc = number of arguments passed in
//argv = list of arguments passed in
int main(int argc, char *argv[]){
  char *flag[2] = {"-l", "-c"};
  //If the user passes in three arguemtns we need to find if flag or file is first
  if(argc == 3){
    //Flag = -l in first position
    if(strcmp(argv[1], flag[0]) == 0){
      numLines(argv[2]);
    }
    //Flag = -c in first position
    if(strcmp(argv[1], flag[1]) == 0){
      numChars(argv[2]);
    }
    //Flag = -l in third position
    if(strcmp(argv[2], flag[0]) == 0){
      numLines(argv[1]);
    }
    //Flag = -c in third position
    if(strcmp(argv[2], flag[1]) == 0){
      numChars(argv[1]);
    }
  }
  //If the user passes in two arguemtns we need to find if flag exists
  if(argc == 2){
    //Flag = -l in second position
    if(strcmp(argv[1], flag[0]) == 0){
      consoleLines();
    }
    //Flag = -c in second position
    if(strcmp(argv[1], flag[1]) == 0){
      consoleChars();
    }
    //OR the user has passed in a fileName
    else{
      readFile(argv[1]);
    }
  }
  return 0;
}
