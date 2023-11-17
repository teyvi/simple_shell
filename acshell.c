#include "ac_shell.h"
/**
 * process_input - process the user input
 * @line: user input string
 *
 * Return: (1) if successful, (0) otherwise
 */
int process_input(char *line)
{
	char *line_arg[1024];
	char *tkn;
	pid_t cpid;

	int argid = 0;

	tkn = strtok(line, " \n");

	while (tkn != NULL)
	{
		line_arg[argid] = tkn;
		tkn = strtok(NULL, " \n");
		argid++;
	}
	line_arg[argid] = NULL;

	if (argid > 0 && strcmp(line_arg[0], "exit") == 0)
		return (0);

	if (argid == 0)
		return (1);

	cpid = fork();

	if (cpid == -1)
	{
		perror("Fork failed");
		free(line);
		return (-1);
	}
	else if (cpid == 0)
	{
		execute_command(line_arg);
	}
	else
	{
		wait_for_child(cpid);
	}

	return (1);
}

/**
 * execute_command - execute the command
 * @args: array of arguments for the command
 */
void execute_command(char *args[])
{
	char *ACPATH;

	if (strchr(args[0], '/') != NULL)
	{
		ACPATH =strdup(args[0]);
	}
	else
	{
		ACPATH = pathdir(args[0]);
	}

	if (ACPATH != NULL)
	{
		execve(ACPATH, args, environ);
		perror("Execve failed");
		_exit(EXIT_FAILURE);
	}
	else
	{
		const char *error = "Executable not found\n";

		write(2, error, strlen(error));
		_exit(EXIT_FAILURE);
	}
}

/**
 * wait_for_child - wait for the child process to complete
 * @cpid: child process ID
 */
void wait_for_child(pid_t cpid)
{
	int stat;

	if (waitpid(cpid, &stat, 0) == -1)
	{
		perror("Waitpid failed");
	}
}

/**
 * main - entry point for the custom shell
 *
 * Return: (0) on successful execution
 */
int main(void)
{
	ssize_t fromuser;
	char *line = NULL;
	size_t len = 0;

	while (1)
	{
		display_prompt();

		fromuser = getline(&line, &len, stdin);

		if (fromuser == -1)
		{
			handle_input_error(line);
		}
		else if (fromuser == 1)
		{
			continue;
		}
		else
		{
			if (!process_input(line))
				break;
		}
	}
	free(line);

	return (0);
}

/**
 * handle_input_error - handle input error
 * @line: input to be freed
 */
void handle_input_error(char *line)
{
	perror("Error reading input");
	if (line != NULL)
	{
		free(line);
	}
	exit(EXIT_FAILURE);
}

