#include "shell.h"
/**
 * exit_function - exits the program with status
 * @line: program input
 * Return: void
*/
void exit_function(char *line)
{
	int exit_status;
	char *exit_arg;

	exit_arg = line + 5;
	if (*exit_arg == '\0')
	exit(EXIT_SUCCESS);
	else
	{
		exit_status = atoi(exit_arg);
		if (exit_status == 0)
			exit(EXIT_SUCCESS);
		else
			exit(exit_status);
	}
}
