#include "shell.h"

/**
 * tokenize - tokenize string on delimeter
 * @line: String to be tokenized
 * @delimeter: delimeter given
 * Return: Array of strings
*/
char **tokenize(char *line, const char *delimeter)
{
	char *token = NULL, **tokens = NULL;
	int count = 0;

	if (line == NULL)
		return (NULL);
	tokens = malloc(sizeof(char *) * strlen(line) + 1);

	if (tokens == NULL)
	{
		perror("Memory Allocation Failed");
		free(line);
		free(tokens);
		exit(EXIT_FAILURE);
	}
	token = strtok(line, delimeter);
	while (token != NULL)
	{
		tokens[count] = malloc(strlen(token) + 1);
		if (tokens[count] == NULL)
		{
			perror("Memory Allocation Failed");
			free(tokens);
			return (NULL);
		}
	strcpy(tokens[count++], token);
	token = strtok(NULL, delimeter);
	}
	tokens[count] = NULL;
	return (tokens);
}