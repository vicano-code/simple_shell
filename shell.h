#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>

#define MAX_ARGS 20
#define MAX_LINE 50

extern char **environ;
int _putchar(char c);
int _getpid(void);
char *_strcpy(char *dest, char *src);
char *_strchr(char *s, char c);
void sigintHandler(int signum);
int cmd_array(char *line, char **cmd);
void _setenv(char **cmd);
void exit_shell(char **cmd);
int execute_cmd(char **cmd, char *str, int count);
char *get_cmd_path(char **cmd, char *cmd_path);
void _pcerror(char *str, int n, char *c, char *s);
void change_dir(char **cmd, char *str, int n);

#endif
