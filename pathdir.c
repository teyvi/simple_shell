#include "ac_shell.h"

/**
 * append_path - Append a command to a directory in the PATH.
 * @ddir: The directory in the PATH.
 * @cmd: The command to append.
 *
 * Return: A pointer to the full path of the command if found, or NULL.
 */
char *append_path(const char *ddir, const char *cmd)
{
	char cmd_dir[1024];
	char *result = NULL;

	strcpy(cmd_dir, ddir);
	if (cmd_dir[strlen(cmd_dir) - 1] != '/')
	{
		strcat(cmd_dir, "/");
	}

	strcat(cmd_dir, cmd);

	if (access(cmd_dir, X_OK) == 0)
	{
		result = strdup(cmd_dir);
	}

	return (result);
}

/**
 * pathdir - Find the full path of a command in the PATH directories.
 * @cmd: The command to search for.
 *
 * Return: A pointer to the full path of the command if found, or NULL.
 */
char *pathdir(const char *cmd)
{
	char *path = getenv("PATH");
	char *path_duplicate;
	char *result = NULL;

	if (path == NULL)
	{
		perror("Error getting PATH");
		return (NULL);
	}

	path_duplicate = strdup(path);
	if (path_duplicate == NULL)
	{
		perror("Error duplicating PATH");
		return (NULL);
	}

	{
		char *ddir = strtok(path_duplicate, ":");

		while (ddir != NULL)
		{
			result = append_path(ddir, cmd);
			if (result != NULL)
			{
				break;
			}

			ddir = strtok(NULL, ":");
		}
	}

	free(path_duplicate);

	return (result);
}
