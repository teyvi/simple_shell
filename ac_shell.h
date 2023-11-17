#ifndef AC_SHELL_H
#define AC_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

extern char **environ;

/**
 * ac_print - Print a message to the standard output.
 * @message: The message to be printed.
 */
void ac_print(const char *message);

/**
 * pathdir - Find the full path of a command in the PATH directories.
 * @cmd: The command to search for.
 * Return: A pointer to the full path of the command if found, or NULL.
 */
char *pathdir(char *cmd);

/**
 * display_prompt - Display the shell prompt.
 */
void display_prompt(void);

/**
 * print_environment - Print the environment variables.
 */
void print_environment(void);

#endif
