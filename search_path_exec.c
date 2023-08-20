#include "main.h"

/**
 * search_command - searches the path and executes if found
 * @head_dir: A linked list of directories in the PATH
 * @head: A linked list of the user input tokens
 *
 * Return: Nothing
 */
char *search_command(tokens_t *head_dir, char *command)
{
        char *search_path = NULL;
        tokens_t *temp;

        temp = head_dir;
        while(temp != NULL)
        {
                search_path = (char *) malloc(strlen(temp->token) + strlen(command) + 2);
                if (search_path == NULL)
                {
                        return (NULL);
                }
                strcpy(search_path, temp->token);
                strcat(search_path, "/");
                strcat(search_path, command);
		printf("The search path is %s\n", search_path);
                if ((access(search_path, F_OK) == 0))
                {
                        printf("Path found in acc: %s\n", search_path);
                        break;
                }
                temp = temp->next;
                free(search_path);
                search_path = NULL;
        }
        if (search_path != NULL) 
                return (search_path);
        perror(command);
        return (NULL);
}
/**
 * execute_command - executes a command path found in PATH
 * @head: A linked list of the commandline arguments
 * 
 * Return: 0 on failure, 1 on Success
 */
int execute_command(tokens_t *head, char *command, char **env)
{
        char **args = NULL;
        pid_t pid;
        int status;

        args = initialize_array(head, args);
        args[0] = strdup(command);
        pid = fork();
        if (pid == -1)
        {
                perror("fork");
                exit(errno);
        }
        else if (pid == 0)
        {
                execve(args[0], args, env);
                perror(args[0]);
                free_array(args);
                args = NULL;
                exit(errno);
        }
        else
        {
                wait(&status);
                if (args)
                {
                        free_array(args);
                        args = NULL;
                }
        }
        return (status);
}
/**
 * initialize_array - initializes an array of pointers
 * @head: A linked list with user tokens
 * @args: An NULL initialized double pointer
 *
 * Return: A dynamically allocated array of pointers
 */
char **initialize_array(tokens_t *head, char **args)
{
        int token_count, i;
        tokens_t *temp;

        token_count = 0;
        for(temp = head; temp != NULL; temp = temp->next)
                token_count++;
        args = (char **)malloc(sizeof(char *) * (token_count + 1));
        for (temp = head->next, i = 1; temp != NULL; temp = temp->next, i++)
        {
                args[i] = strdup(temp->token);
                temp = temp->next;
        }
        args[i] = NULL;
        return (args);
}
