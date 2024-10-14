/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:55:49 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/13 15:56:38 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	has_pipe_or_not(t_node *sentence)
{
	if (sentence->next)
		return (TRUE);
	return (FALSE);
}

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
