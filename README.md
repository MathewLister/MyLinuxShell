# MyLinuxShell

Wrote my own Linux shell in C. A shell interpreter, often just called a shell or command line interpreter, is a program that continually loops, accepting user input.  The shell interprets the user’s input to execute programs, run built-in functions, etc.  Here is a high-level pseudocode sketch of the behavior of a shell:
``` c
while true {
  read user input
  if input is built-in command
    handle it
  else if user input is a program in path
    fork child process
    wait for child process to complete
  else
    error
}
```
## Command List
* exit Usage: exit
* help Usage: help
* my_shell Usage: ./myshell [-h]
* pwd Usage: pwd
* cd Usage: cd [dir]
* setpath Usage: setpath \<dir> [dir] … [dir]
* new_cat Usage: new_cat [file.txt]
* new_echo Usage: new_echo [arg] [arg] … [arg]

## Redirection
* Usage: command > filename

Note:
  Default PATH variable is set to /bin. If you want to execute a non-built-in command
  use setpath to overwrite PATH variable for a new place to look for executables.

  parameters in [] are optional, parsameters in <> are required. The | (pipe) means “or.”
