#include "ac_shell.h"

/**
 * interactive_mode - Run the shell in interactive mode
 */
void interactive_mode(void)
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
			if (feof(stdin))
			{
				free(line);
				write(STDOUT_FILENO, "\n", 1);
				_exit(0);
			}
			else
			{
				handle_input_error(line);
			}
		}
		else if (fromuser == 1)
		{
			continue;
		}
		else
		{
			if (!process_input(line))
			{
				break;
			}
		}
	}

	free(line);
}

/**
 * non_interactive_mode - Run the shell in non-interactive mode
 */
void non_interactive_mode(void)
{
	ssize_t fromuser;
	char *line = NULL;
	size_t len = 0;

	while ((fromuser = getline(&line, &len, stdin)) != -1)
	{
		if (fromuser > 1)
		{
			process_input(line);
		}
	}

	free(line);
}

