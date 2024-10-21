
#include "../../../includes/minishell.h"

/**
 * @brief has_pipe_or_not - Checks if there is a pipe in the command list.
 *
 * This function checks if the given linked list of `t_node` structures
 * contains more than one node. If there is more than one node, it
 * indicates that there is a need for pipe functionality when executing
 * commands. This is a critical check for the minishell to determine
 * how to handle command execution and output redirection between commands.
 *
 * @param sentence: A pointer to the head of the linked list of nodes
 *                  representing the command sequence.
 *
 * @return int: Returns TRUE if there is more than one node in the
 *              list (indicating the presence of a pipe), or FALSE
 *              otherwise.
 */

int	has_pipe_or_not(t_node *sentence)
{
	if (sentence->next)
		return (TRUE);
	return (FALSE);
}

/**
 * @brief make_pipe - Configures pipes between commands in a command list.
 *
 * This function sets up the necessary pipe file descriptors for
 * inter-process communication between commands in the linked list
 * of `t_node` structures. It calculates the number of pipes required
 * based on the size of the command list and invokes the `pipe_config`
 * function for each node in the list. This function is crucial for
 * the proper execution of piped commands in the minishell.
 *
 * @param sentence: A pointer to the head of the linked list of nodes
 *                  representing the command sequence.
 *
 * @return void: This function does not return a value.
 *
 * @note After configuring pipes, the output file descriptor of the
 *       last node is reset to standard output (`STDOUT_FILENO`) to
 *       ensure that any output after the pipeline goes to the console.
 */

void	make_pipe(t_node *sentence)
{
	t_node	*node;
	int		pipes;
	int		i;

	i = 0;
	node = sentence;
	pipes = node_list_size(node) - 1;
	while (i < pipes && node)
	{
		pipe_config(node);
		node = node->next;
		i++;
	}
	if (node)
	{
		node->fd_out = STDOUT_FILENO;
	}
}

/**
 * @brief pipe_config - Sets up a single pipe for a given node.
 *
 * This function creates a pipe and assigns the appropriate file
 * descriptors to the output of the current node and the input of the
 * next node in the linked list of `t_node` structures. This is
 * essential for enabling communication between processes executing
 * piped commands in the minishell.
 *
 * @param node: A pointer to the node that requires pipe configuration.
 *
 * @return int: Returns NO_ERROR on success, or ERROR on failure.
 *
 * @note If the pipe creation fails, an error message is printed using
 *       `perror`, and the function returns ERROR. If there is no next
 *       node (i.e., the last command), both ends of the pipe are closed
 *       to prevent resource leaks.
 */

int	pipe_config(t_node *node)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (perror((strerror(errno))), ERROR);
	node->fd_out = pipe_fd[1];
	if (node->next)
		node->next->fd_in = pipe_fd[0];
	else
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	return (NO_ERROR);
}
