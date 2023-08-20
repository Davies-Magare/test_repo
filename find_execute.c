#include "main.h"

/**
 * full_command - searches for the full command
 * @head: The entry into a linked list
 *
 * Return: 1 if the command was found and run
 * returns 0 if otherwise
 */
int full_command(tokens_t *head, char **envp)
{
        int argct, status, i;
        char **args = NULL;
        tokens_t *temp;
        pid_t pid;

        if (access(head->token, X_OK) == -1)
                return (0);
        temp = head;
        for (argct = 0; temp != NULL; argct++)
        {
                argct++;
                temp = temp->next;
        }
        argct++;
        args = (char **)malloc(sizeof(char *) * argct);
        for (temp = head, i = 0; temp != NULL; temp = temp->next)
                args[i++] = strdup(temp->token);
        args[i] = NULL;
        /*execute */
        pid = fork();
        if (pid < 0)
        {
                free_array(args);
                exit(errno);
        }
        else if (pid == 0)
        {
                execve(args[0], args, envp);
                perror(args[0]);
                free_array(args);
                args = NULL;
        }
        else
                wait(&status);
                if (args)
                        free_array(args);
        return (1);
}
/**
 * free_array - frees an array of pointers
 * @array: An array of pointers
 *
 * Return: Nothing.
 */
void free_array(char **array)
{
	int i;

	for (i = 0; array[i] != NULL; i++)
		free(array[i]);
	free(array);
}
















