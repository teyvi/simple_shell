#include "ac_shell.h"

/**
 * ac_print - prints out a message
 * @message: The message to be printed.
 */

void ac_print(const char *message)
{
	write(STDOUT_FILENO, message, strlen(message));
}
