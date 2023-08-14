#ifndef MAIN_H
#define MAIN_H
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#define BUFSIZE 1024
char **tokenize_input(char *str);
int execute_shell(char **tokens);
char *find_full_path(char *command, char copy_path[]);

#endif
