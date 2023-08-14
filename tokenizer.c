#include "main.h"
/**
 * tokenize_input: Tokenizes a string into an array of strings
 * @str: A string
 *
 * Return: On success, an array of strings. Otherwise return NULL
 */


char **tokenize_input(char *str)
{
	char **tokens;
	char *token;
	char *delim = " \t\n";
	int i, new_size;
	if (str == NULL)
		return (NULL);

	tokens = (char **)malloc(BUFSIZE * sizeof(char *));
	if (tokens == NULL)
		return (NULL);
	token = strtok(str, delim);
	i = 0;
	while (token != NULL)
	{
		tokens[i++] = token;
		if (i >= BUFSIZE)
		{
			new_size = BUFSIZE * 2;
			tokens = realloc(tokens, new_size);
		}
		token = strtok(NULL, delim);
	}
	tokens[i] = NULL;
	return (tokens);
}
