#include "main.h"
/**
 * main - Runs the shell
 *
 * Return: Always 0 (Success)
 */

int main(void)
{
	char *prompt = "$ ";
	char *buffer = NULL; char copy_path[300];
	ssize_t getline_ret;
	size_t size;
	char **tokens;
	char *full_path;
	char *err_message = "Invalid input";

	size = 0;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(1, prompt, 2);
		getline_ret = getline(&buffer, &size, stdin);
		printf("%s\n", buffer);
		if (getline_ret)
		{
			tokens = tokenize_input(buffer);
			printf("%s\n", tokens[0]);
			full_path = find_full_path(tokens[0], copy_path);
			if (!full_path)
			{
				free(tokens);
				continue;
			}
			tokens[0] = full_path;
			execute_shell(tokens);
			free(tokens);
			free(buffer);
			continue;
		}
		else
		{
			write(2, err_message, strlen(err_message));
			break;
		}
	}
	return (0);
}
