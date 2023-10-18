#include "shell.h"

/**
 * main - Entry point
 * @ac: argument count
 * @av: argument vector
 * @env: environment variable
 * Return: 0 on success, non zero on failure
 */
int main(int ac, char **av, char **env)
{
	char *line, *args[16], *delimeter = " \n";
	size_t bufsize;
	ssize_t chars_count;
	int i, status = 0;
	pid_t pid = 0;

	(void)ac;

	line = NULL;
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
			args[0] = strtok(line, delimeter);
			if (strcmp(args[0], "exit") == 0)
			{
				/*free_double_pointer(args, line);*/
				exit(EXIT_SUCCESS);
			}
			else if (strcmp(args[0], "env") == 0)
			{
				get_env(env);
				/*free_double_pointer(args, line);*/
				continue;
			}
			while (args[i] != NULL)
			{
				i++;
				args[i] = strtok(NULL, delimeter);
				/*args[i] = NULL;*/
			}
			if (check_exec_path(&args[0], av[0]) == 1)
			{
				

				pid = fork();

			if (pid == 0)
				{
		if (execve(args[0], args, NULL) == -1)
			perror(av[0]);
		exit(EXIT_SUCCESS);
	}
	else if (pid < 0)
	{
		perror(av[0]);
		return (1);
	}
	else
	{
		do
		{
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
			}
				/*execute(&args[0], av[0], env);*/
			/*free_double_pointer(args, line);*/
		}
		/*line = NULL;
		bufsize = 0;
		free(line);*/
	}
	return (0);
}