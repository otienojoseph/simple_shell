#include "shell.h"

/**
 * execute - creates child process for commands
 * @args: commands entered
 * @av: argument vector
 * @env: environment of command
 * Return: Status of process
 */
int execute(char **args, char *av, char **env)
{
	pid_t pid = 0;
	int status = 0;

	(void)env;

	pid = fork();

	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
			perror(av);
		exit(EXIT_SUCCESS);
	}
	else if (pid < 0)
	{
		perror(av);
		return (1);
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return (status);
}
