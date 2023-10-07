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
	size_t bufsize;
	ssize_t chars_count;

	(void)ac;

	line = NULL;
	bufsize = 0;
	args = NULL;
	chars_count = 0;

	while (1)
	{
		if(isatty(STDIN_FILENO) == 1)
			write(STDOUT_FILENO, "($) ", strlen("($) "));
		chars_count = getline(&line, &bufsize, stdin);
		if (chars_count == -1)
		{
			free(line);
			return (EXIT_SUCCESS);
		}
		else if (*line == '\n')
			free(line);
		else
		{
			line[strlen(line) - 1] = '\0';
			args = tokenize(line, " \0\n\t");
			if (strcmp("exit", args[0]) == 0)
			{
				break;
			}
			free(line);

			execute(args, av[0]);

		}
		/*fflush(stdin);*/
		line = NULL;
		bufsize = 0;
		free(line);
	}
	return (EXIT_SUCCESS);
}

/**
 * tokenize - tokenize string on delimeter
 * @line: String to be tokenized
 * @s: delimeter given
 * Return: Array of strings
*/
char **tokenize(char *line, const char *s)
{
	char *token = NULL, **tokens = NULL;
	int buf_size = 0, count = 0;

	if (line == NULL)
		return (NULL);
	buf_size = strlen(line);
	tokens = malloc(sizeof(char *) * (buf_size + 1));

	if (tokens == NULL)
	{
		perror("Memory Allocation Failed");
		free(line);
		free(tokens);/*??*/
		exit(EXIT_FAILURE);
	}
	token = strtok(line, s);
	while (token != NULL)
	{
		tokens[count] = malloc(strlen(token) + 1);
		if (tokens[count] == NULL)
		{
			perror("Memory Allocation Failed");
			free(tokens);/*??*/
			return (NULL);
		}
	strcpy(tokens[count], token);
	token = strtok(NULL, s);
	count++;
	}
	tokens[count] = NULL;
	return (tokens);
}

/**
 * execute - creates child process for commands
 * @args: commands entered
 * @av: argument vector
 * Return: Status of process
*/
int execute(char **args, char *av)
{
	pid_t pid = 0;
	int status = 0;
	struct stat s;

	if (stat(av, &s) == 0)
	{
		if (av)
		{
			pid = fork();

			if (pid == 0)
			{
				if (execve(args[0], args, environ) == -1)
					perror(av);
				exit(EXIT_FAILURE);
			}
			else if (pid < 0)
				perror(av);
			else
			{
				do {
					waitpid(pid, &status, WUNTRACED);
				} while (!WIFEXITED(status) && !WIFSIGNALED(status));
			}
		}
	}
	else
		perror(av);
	return (status);
}
