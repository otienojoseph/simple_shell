#include "shell.h"

/**
 * main - Entry point
 * @ac: argument count
 * @av: argument vector
 * @env: path environment
 * Return: 0 on success, non zero on failure
 */
int main(int ac, char **av)
{
	char *line, **args;
	char *delimeter = " \n\t";
	size_t bufsize;
	ssize_t chars_count;
	int i;

	(void)ac;

	line = NULL;
	args = NULL;
	bufsize = 0;
	chars_count = 0;

	while (1)
	{
		if(isatty(STDIN_FILENO) == 1)
			write(STDOUT_FILENO, "($) ", strlen("($) "));
		chars_count = getline(&line, &bufsize, stdin);
		if (chars_count == -1)
		{
			free(line);
			return (0);
		}
		else if (space_check(line) == 1)
		{
				continue;
		}

		else
		{
			args = tokenize(line, delimeter);
			if (strcmp(args[0], "exit") == 0)
			{
				free(line);
				exit(EXIT_SUCCESS);
			}
			else if (strcmp(args[0], "env") == 0)
			{
				get_env(environ);
				continue;
			}

			i = 0;
			while (args[i] != NULL)
			{
				i++;
				args[i] = strtok(NULL, delimeter);
			}
			
			if (check_exec_path(&args[0]) == 1)
			{
				execute(&args[0], av[0]);
			}
		}
		line = NULL;
		bufsize = 0;
		free(line);
	}
	return (0);
}