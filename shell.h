#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

#define BUFFER 1024

extern char **environ;
char **tokenize(char *line, const char *delimeter);
int check_exec_path(char **str, char *av);
int execute(char **args, char *av, char **env);
void get_env(char **env);
int space_check(char *line);
char *get_env_var(const char *env);
void check_getline_count(char *line);
void free_double_pointer(char **args, char *line);
void exit_function(char *line);

#endif
