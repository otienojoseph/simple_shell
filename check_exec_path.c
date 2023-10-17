#include "shell.h"

/**
 * check_exec_path - check if the command exist in the
 * path, if it does not creat a path and append it to the directory
 * @str: pointer to the command.
 * Return: return 1 on success, 0 on failure.
 */
int check_exec_path(char **str)
{
	char *path_copy, *token, *full_command;
	char path_buf[BUFFER], buffer[BUFFER];
	unsigned int i;

	if (access(*str, X_OK) == 0)
		return (1);
	path_copy = get_env_var("PATH");
	if (path_copy == NULL)
		return (0);
	strcpy(path_buf, path_copy);
	token = strtok(path_buf, ":");
	while (token != NULL)
	{
		full_command = malloc(strlen(token) + strlen("/") + strlen(*str) + 1);
		if (full_command == NULL)
		{
			perror(*str);
			free(full_command);
			return (0);
		}
		strcpy(full_command, token);
		strcat(full_command, "/");
		strcat(full_command, *str);
		if (access(full_command, X_OK) == 0)
		{
			for (i = 0; full_command[i] != '\0'; i++)
				buffer[i] = full_command[i];
			buffer[i] = '\0';
			free(full_command);
			*str = buffer;
			return (1);
		}
		free(full_command);
		token = strtok(NULL, ":");
	}
	perror(*str);
	return (0);
}
