#include "ac_shell.h"

/**
 * main - entry point for the custom shell
 *
 * Return: 0 on sucessful execution
 */
int main(void)
{
	ssize_t fromuser;
	char *line = NULL;
	size_t len = 0;
	const char *delimiter = " \n";
	char *tkn;
	char *line_arg[1024];
	pid_t cpid;

	while (1)
	{
		display_prompt();

		fromuser = getline(&line, &len, stdin);

		if (fromuser == -1)
		{
			if (errno == EOF)
			{
				break;
			}
			else
			{
				perror("Error reading input");
				free(line);
				return (-1);
			}
		}
		else if (fromuser == 1)
		{
			continue;
		}
		else
		{
			int argid = 0;

			tkn = strtok(line, delimiter);

			while (tkn != NULL)
			{
				line_arg[argid] = tkn;
				tkn = strtok(NULL, delimiter);
				argid++;
			}
			line_arg[argid] = NULL;

			if (argid > 0 && strcmp(line_arg[0], "exit") == 0)
			{
				break;
			}

			if (argid == 0)
			{
				continue;
			}

			cpid = fork();

			if (cpid == -1)
			{
				perror("Fork failed");
				free(line);
				return (-1);
			}
			else if (cpid == 0)
			{
				char *ACPATH = pathdir(line_arg[0]);

				if (ACPATH != NULL)
				{
					execve(ACPATH, line_arg, environ);
					perror("Execve failed");
					free(line);
					_exit(EXIT_FAILURE);
				}
				else
				{
					const char *error = "Executable not found\n";

					write(2, error, strlen(error));
					free(line);
					_exit(EXIT_FAILURE);
				}
			}
			else
			{
				int stat;

				if (waitpid(cpid, &stat, 0) == -1)
				{
					perror("Waitpid failed");
				}
			}
		}
	}

	free(line);

	return (0);
}

/**
 * print_environment - prints the current environment variables
 */
void print_environment(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		write(1, *env, strlen(*env));
		write(1, "\n", 1);
		env++;
	}
}
