#ifndef AC_SHELL_H
#define AC_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
 * display_prompt - Display the shell prompt.
 */
void display_prompt(void);

/*
 * pathdir - Get the directory path for a given command.
 */
char *pathdir(const char *cmd);

/*
 * process_input - Process the input line.
 */
int process_input(char *line);

/*
 * print_environment - Print the environment variables.
 */
void print_environment(void);

/*
 * execute_command - Execute the given command.
 */
void execute_command(char *args[]);

/**
 * handle_input_error - Handles invalid user input errors in the shell.
 */
void handle_input_error(char *line);

/*
 * wait_for_child - Wait for the child process to complete.
 */
void wait_for_child(pid_t cpid);

/**
 * ac_print - Prints a message to the standard output.
 *
 * @message: The message to be printed.
 */
void ac_print(const char *message);

/*
 * main - Entry point of the program.
 *
 * Return: Always 0.
 */
int main(void);

extern char **environ;

/*
 * append_path - Append a command to a directory in the PATH.
 * @ddir: The directory in the PATH.
 * @cmd: The command to append.
 *
 * Return: A pointer to the full path of the command if found, or NULL.
 */
char *append_path(const char *ddir, const char *cmd);

#endif

