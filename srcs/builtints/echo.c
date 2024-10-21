
#include "../../includes/minishell.h"

/**
 * my_echo - Implements the behavior of the 'echo' built-in command.
 *
 * This function replicates the behavior of the shell's 'echo' command. It 
 * prints the words passed as tokens to the specified file descriptor, with 
 * an optional suppression of the trailing newline using the `-n` flag.
 *
 * If no tokens are passed, it simply prints a newline. If the first token is 
 * `-n`, it suppresses the newline at the end of the output.
 *
 * @param node: A linked list of tokens, representing the arguments passed to 
 *              the 'echo' command.
 * @param fd: The file descriptor to which the output should be written.
 *
 * @return int: Returns `NO_ERROR` after writing to the file descriptor.
 */

int	my_echo(t_tokens *node, int fd)
{
	int			flag_nl;
	t_tokens	*temp;

	temp = node;
	flag_nl = ON;
	if (node == NULL)
	{
		my_putstr_fd("\n", fd);
		return (NO_ERROR);
	}
	if (strcmp(temp->word, "-n") == 0)
	{
		flag_nl = OFF;
		temp = temp->next;
	}
	while (temp)
	{
		my_putstr_fd(temp->word, fd);
		if (temp->next != NULL)
			my_putstr_fd(" ", fd);
		temp = temp->next;
	}
	if (flag_nl == ON)
		my_putstr_fd("\n", fd);
	return (NO_ERROR);
}
