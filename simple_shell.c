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
		/* else if (*line == '\n')
		{
			free(line);
		} */
		else
		{
			/* line[strlen(line) + 1] = '\0'; */
			args = tokenize(line, delimeter);
			if (strcmp(args[0], "exit") == 0)
			{
				free(line);
				exit(EXIT_SUCCESS);
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

	pid = fork();

	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
			perror(av);
		exit(EXIT_FAILURE);
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
