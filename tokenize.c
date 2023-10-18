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
	int i, count = 0;
	size_t line_len = strlen(line);

	if (line == NULL)
		return (NULL);
	tokens = malloc(sizeof(char *) * (line_len + 1));

	if (tokens == NULL)
	{
		perror("Memory Allocation Failed");
		free(tokens);
		free(line);
		return (NULL);
	}
	token = strtok(line, delimeter);
	while (token != NULL)
	{
		tokens[count] = malloc(strlen(token) + 1);
		if (tokens[count] == NULL)
		{
			perror("Memory Allocation Failed");
			for (i = 0; i < count; i++)
			{
				free(tokens[i]);
			}
			free(tokens);
			free(line);
			return (NULL);
		}
		strcpy(tokens[count], token);
		count++;
		token = strtok(NULL, delimeter);
	}
	tokens[count] = NULL;
	free(line);
	return (tokens);
}
