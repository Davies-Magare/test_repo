#include "main.h"

/**
 * main - driver function for the code
 * @argc: The argument count
 * @argv: An array of string arguments to main

 * Return: Always 0 (Success)
 */
int main(int __attribute__((unused)) argc, char __attribute__((unused)) *argv[], char **envp)
{
        ssize_t getline_ret;
        char *buffer = NULL, *prompt = "$ ", *cpy_buf, *path;
        size_t size;
        tokens_t *head, *head_dir;
	char *job_path, *full_path;
	int status;

        while (1)
        {
                if (isatty(STDIN_FILENO))
                        write(1, prompt, strlen(prompt));
                getline_ret = getline(&buffer, &size, stdin);
                if (getline_ret == -1)
                {
                        free(buffer);
                        exit(errno);
                }

                cpy_buf = check_buffer(buffer);
                if (cpy_buf[0] == '\n')
                        continue;
                head = tokenize_input(cpy_buf);
		if (strcmp(head->token, "exit") == 0)
		{
			free(buffer);
			free_list(head);
			exit(errno);
		}
		path = find_path(envp);
		job_path = strdup(path);
		head_dir = tokenize_input(job_path);
		if ((full_command(head, envp) == 0))
		{
			full_path = search_command(head_dir, head->token);
			if (full_path)
			{
				printf("Path to pass: %s\n", full_path);
				status = execute_command(head, full_path, envp);
				printf("%i\n", status);
			}

		}
		free_list(head);
		free_list(head_dir);
		free(job_path);
	}
	free(buffer);
	return (0);
}
 /**
  * check_buffer - locates the first non_space character in input
  * @buffer: The buffer containing user input
  *
  * Return: Nothing
  */
char *check_buffer(char *buffer)
{
        int i;

        for (i = 0; buffer[i] != '\0'; i++)
                if (buffer[i] != ' ')
                        break;
        if (buffer[i] == '\0')
                return (NULL);
        return (buffer + i);
}


