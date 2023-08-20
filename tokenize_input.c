#include "main.h"

/**
 * tokenize_input - tokenizes the user input
 * @buffer: User input buffer
 *
 * Return: A linked list with the buffer tokens
 * On failure, return NULL
 */
tokens_t *tokenize_input(char *buffer)
{
	char *token; 
	char *delimeter = " \t\n:";
	tokens_t *head, *to_fill, *new_node; 
	
	if (buffer[0] == '\0')
		return (NULL);
	token = strtok(buffer, delimeter);
	if (token != NULL)
	{
		head = (tokens_t *) malloc(sizeof(tokens_t));
		if (head == NULL)
			return (NULL);
		head->token = token;
		head->next = NULL;
	}
	to_fill = head;
	token = strtok(NULL, delimeter);
	while(token != NULL)
	{
		new_node = (tokens_t *)malloc(sizeof(tokens_t));
		if (new_node == NULL)
			return (NULL);
		new_node->token = token;
		new_node->next = NULL;
		to_fill->next = new_node;
		to_fill = new_node;
		token = strtok(NULL, delimeter);
	}
	return (head);
}
/**
 * free_list - frees a linked list
 * @head: The head of the list
 *
 * Return: Nothing
 */
void free_list(tokens_t *head)
{
	tokens_t *temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
}	
