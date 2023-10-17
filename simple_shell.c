#include "shell.h"

/**
 * main - Entry point
 * @ac: argument count
 * @av: argument vector
 * Return: 0 on success, non zero on failure
 */
int main(int ac, char **av, char **env)
{
	char *line, **args, *delimeter = " \n";
	size_t bufsize;
	ssize_t chars_count;
	int i;

	(void)ac;

	line = NULL, args = NULL;
	bufsize = 0, chars_count = 0, i = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			write(STDOUT_FILENO, "($) ", strlen("($) "));
		chars_count = getline(&line, &bufsize, stdin);
		if (chars_count == -1)
			check_getline_count(line);
		else if (space_check(line) == 1)
			continue;
		
		else
		{
			args = tokenize(line, delimeter);
			if (strcmp(args[0], "exit") == 0)
				free_and_exit(line);
			else if (strcmp(args[0], "env") == 0)
			{
				get_env(env);
				continue;
			}
			while (args[i] != NULL)
			{
				i++;
				args[i] = strtok(NULL, delimeter);
				args[i] = NULL;
			}
			if (check_exec_path(&args[0], av[0]) == 1)
				execute(&args[0], av[0], env);
		}
		line = NULL;
		bufsize = 0;
		free(line);
	}

	return (0);
}