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
 * space_check - check if the command is spaces only
 * @line: that array is a pointer
 * Return: 1 if the string has no letters and only spaces
 */
int space_check(char *line)
{
	unsigned int i;

	i = 0;

	while (i < strlen(line) - 1)
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

/**
 * get_env_var - get the enviroment variables.
 * @env: pointer to a pointer to strings
 * Return: env variable
 */
char *get_env_var(const char *env)
{
	int i;
	size_t length;

	i = 0;
	length = strlen(env);
	while (environ[i] != NULL)
	{
		if (strncmp(environ[i], env, length) == 0 && environ[i][length] == '=')
		{
			return (environ[i] + length + 1);
		}
		i++;
	}
	return (NULL);
}

/**
 * check_getline_count - Check getline return count
 * @line: string to count from
 * Return: 0 on success
 */
void check_getline_count(char *line)
{
	write(0, "\n", 2);
	free_and_exit(line);
}

/**
 * free_and_exit - Free line pointer and exit
 * @line: pointer
 * Return: 0 on success
 */
void free_and_exit(char *line)
{
	(void)line;

	/* free(line); */
	exit(EXIT_SUCCESS);
}
