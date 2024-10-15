/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:17:25 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/14 23:06:58 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * @brief node_list_size - Counts the number of nodes in a linked list.
 *
 * This function iterates through a linked list of `t_node`
 * structures, incrementing a counter for each node encountered.
 * It is useful for determining the size of the command list
 * in the minishell, which can be important for managing resources
 * and executing commands correctly.
 *
 * @param node: A pointer to the head of the linked list of nodes.
 *
 * @return int: The total number of nodes in the list.
 *              If the list is empty, returns 0.
 */

int	node_list_size(t_node *node)
{
	int	i;

	i = 0;
	while (node)
	{
		i++;
		node = node->next;
	}
	return (i);
}

/**
 * @brief do_dup2 - Redirects the standard input and output for a node.
 *
 * This function uses the `dup2` system call to duplicate file
 * descriptors, redirecting the standard input (`STDIN_FILENO`)
 * and/or standard output (`STDOUT_FILENO`) to the file descriptors
 * associated with the specified node. This is essential for proper
 * handling of input and output redirection in the minishell,
 * allowing commands to read from and write to files or pipes as
 * specified in the command sequence.
 *
 * @param node: A pointer to the node containing the file descriptors
 *              for input and output redirection.
 *
 * @return void: This function does not return a value.
 *
 * @note If the node's input descriptor is not the standard input,
 *       it is duplicated and closed, and similarly for the output
 *       descriptor.
 */

void	do_dup2(t_node *node)
{
	if (node->fd_in != STDIN_FILENO)
	{
		dup2(node->fd_in, STDIN_FILENO);
		close(node->fd_in);
	}
	if (node->fd_out != STDOUT_FILENO)
	{
		dup2(node->fd_out, STDOUT_FILENO);
		close(node->fd_out);
	}
}

/**
 * @brief close_node_fds - Closes the file descriptors for a specific node.
 *
 * This function closes the input and output file descriptors
 * associated with a given `t_node`, ensuring that no file descriptors
 * leak when a command finishes executing. Properly managing file
 * descriptors is crucial for resource cleanup in the minishell,
 * preventing potential issues with leftover open files or pipes.
 *
 * @param node: A pointer to the node whose file descriptors will be closed.
 *
 * @return void: This function does not return a value.
 *
 * @note The function checks if the file descriptors are not set to
 *       standard input or output before attempting to close them.
 */

void	close_node_fds(t_node *node)
{
	if (node->fd_out != STDOUT_FILENO)
		close(node->fd_out);
	if (node->fd_in != STDIN_FILENO)
		close(node->fd_in);
}

/**
 * @brief close_all_node_fds - Closes the file descriptors for all
 * nodes in the list.
 *
 * This function iterates through a linked list of `t_node` structures
 * and closes the input and output file descriptors for each node.
 * It ensures that all file descriptors are properly released once
 * they are no longer needed, helping to manage system resources
 * effectively in the context of the minishell.
 *
 * @param node: A pointer to the head of the linked list of nodes.
 *
 * @return void: This function does not return a value.
 *
 * @note The function checks each node's file descriptors to ensure
 *       they are not set to standard input or output before closing them.
 *       This prevents unnecessary attempts to close the default file
 *       descriptors.
 */

void	close_all_node_fds(t_node *node)
{
	while (node)
	{
		if (node->fd_out != STDOUT_FILENO)
			close(node->fd_out);
		if (node->fd_in != STDIN_FILENO)
			close(node->fd_in);
		node = node->next;
	}
}
