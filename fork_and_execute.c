#include "main.h"
/**
 * execute_shell - executes commands passed to the shell
 * @tokens: An array of strings of commands passed to the shell
 *
 * Return: On success 1, Otherwise -1 is returned
 */

int execute_shell(char **tokens)
{
	extern char **environ;
	pid_t pid, ret_wait;
	int status;
	
	pid = fork();
	
	if (pid > 0)
	{
		ret_wait = waitpid(-1, &status, 0);
		if (ret_wait == -1)
			return (-1);
	}
	else if (pid == 0)
	{
		execve(tokens[0], tokens, environ);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (1);
}
