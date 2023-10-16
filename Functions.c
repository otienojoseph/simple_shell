#include "shell.h"
/**
 * get_env - get the enviroment variables.
 * @env: pointer to a pointer to strings
 */
void get_env(char **env)
{
	unsigned int i;
	size_t count;

	i = 0;
	while (env[i] != NULL)
	{
		count = 0;
		while (env[i][count] != '\0')
		{
			count++;
		}
		write(1, env[i], count);
		write(1, "\n", 1);
		i++;
	}
}

/**
 * check_space - it will check if the command is spaces
 * only without any letters
 * @array: that array is a pointer
 * Return: 1 if the string has no letters and only spaces
 */
int space_check(char *line)
{
	unsigned int i;

	i = 0;

	while (i < strlen(line) - 1)
	{
		if (line[i] != ' ')
		{
			return (0);
		}
		i++;
	}
	return (1);
}