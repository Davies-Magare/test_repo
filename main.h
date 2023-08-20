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

typedef struct tokens
{ 
	char *token;
	struct tokens *next;
}tokens_t;
tokens_t *tokenize_input(char *buffer);
char *check_buffer(char *buffer);
void free_list(tokens_t *head);
int full_command(tokens_t *head, char **envp);
void free_array(char **array);
char *find_path(char **envp);
tokens_t *tokenize_directory(char *path);
char *search_command(tokens_t *head_dir, char *command);
int execute_command(tokens_t *head, char *command, char **env);
char **initialize_array(tokens_t *head, char **args);
void free_list_dir(tokens_t *head_dir);
#endif
