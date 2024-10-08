/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:17:25 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/07 21:37:22 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	do_dup2(t_node *node)
{
	if (node->fd_out != STDOUT_FILENO)
        dup2(node->fd_out, STDOUT_FILENO);
    if (node->fd_in != STDIN_FILENO)
        dup2(node->fd_in, STDIN_FILENO);
}

void	close_node_fds(t_node *node)
{
	if (node->fd_out != STDOUT_FILENO)
		close(node->fd_out);
	if (node->fd_in != STDIN_FILENO)
		close(node->fd_in);
}

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

void	wait_cmds(t_node *node)
{
	while (node)
	{
		if (node->pid != 0)
			waitpid(node->pid, &node->exit_status, 0);
		node = node->next;
	}
}

void	update_status(t_node *node)
{
	while (node)
	{
		if (node->exit_status != 0)
		{
				if (node->exit_status >= 255)
					g_status(WEXITSTATUS(node->exit_status));
				else
					g_status(node->exit_status);
		}
		else
			g_status(NO_ERROR);
		node = node->next;
	}
}
