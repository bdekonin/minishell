# minishell

This project is a re-write of a basic shell (BASH reference) with limited feature discovery in the process. It was done in collaboration with user @lverdoes.

## Requirements
- Must be written in C
- Must respect the school's coding style (The Norme)
- No memory leaks

## Features
- Implement a series of builtins: `echo`, `cd`, `setenv`, `unsetenv`, `env`, `exit`
- Manage errors without using `errno`, by displaying a message adapted to the error output
- Use the following standard library functions: `malloc`, `free`, `access`, `open`, `close`, `read`, `write`, `opendir`, `readdir`, `closedir`, `getcwd`, `chdir`, `stat`, `lstat`, `fstat`, `fork`, `execve`, `wait`, `waitpid`, `wait3`, `wait4`, `signal`, `kill`, `exit`
- Have a Makefile to build the program
- The binary file must be named `minishell`
- Use Libft
- Handle program interruption (Ctrl + D)

## Usage
Clone the repository and run `make` to compile the program. After that, you can execute the `minishell` binary.

## Contributors
- [@lverdoes](https://github.com/lverdoes)
