#include <stdio.h>

//argc = number of arguments passed in
//argv = list of arguments passed in
void new_echo(int argc, char *argv){
//If the user calls new_echo without any argument
//Print a new line and exit
  if(argc == 1){
    printf("\n");
  }
  //Else print each argument in a line with spaces between just like echo
  //Do this by looping through the argv[]
  else{
    printf("%s ", argv);
  }
  printf("\n");
}
