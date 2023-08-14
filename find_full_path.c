#include "main.h"
/**
 * find_full_path - finds the full path of a command
 * @command: The command whose path is to be found
 * @cpy_path: An empty array to return the path
 *
 * Return: On success, the path to the command, otherwise
 * return NULL
 */

char *find_full_path(char *command, char copy_path[])
{
	char *full_path = getenv("PATH");
	char *path_tok;
	struct stat st;

	if (stat(command, &st) == 0)
		return (command);
	path_tok = strtok(full_path, ":");
	while (path_tok != NULL)
	{
		strcpy(copy_path, path_tok);
		strcat(copy_path, "/");
		strcat(copy_path, command);
		if (stat(copy_path, &st) == 0)
			return (copy_path);
		path_tok = strtok(NULL, ":");
	}
	perror(command);
	return (NULL);
}
