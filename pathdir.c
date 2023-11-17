#include "ac_shell.h"

/**
 * pathdir - Find the full path of a command in the PATH directories.
 * @cmd: The command to search for.
 *
 * Return: A pointer to the full path of the command if found, or NULL.
 */
char *pathdir(char *cmd)
{
	char *path = getenv("PATH");
	char *pathduplicate;
	char cmd_dir[1024];
	char *result = NULL;

	if (path == NULL)
	{
		perror("Error getting PATH");
		return (NULL);
	}

	pathduplicate = strdup(path);
	if (pathduplicate == NULL)
	{
		perror("Error duplicating PATH");
		return (NULL);
	}

	{
		char *ddir = strtok(pathduplicate, ":");

		while (ddir != NULL)
		{
			strcpy(cmd_dir, ddir);
			if (cmd_dir[strlen(cmd_dir) - 1] != '/')
			{
				strcat(cmd_dir, "/");
			}

			strcat(cmd_dir, cmd);

			if (access(cmd_dir, X_OK) == 0)
			{
				result = strdup(cmd_dir);
				break;
			}

			ddir = strtok(NULL, ":");
		}
	}

	free(pathduplicate);

	return (result);
}

