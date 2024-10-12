/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:27:09 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/12 00:21:49 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

extern volatile unsigned int    g_flag;

int executor(t_command *command, t_node *sentence)
{
	t_node	*current_node;
	int	has_pipe;

	if (check_cmds(sentence) == ERROR)
		return (ERROR);
	has_pipe = has_pipe_or_not(sentence);
	if (has_pipe == TRUE)
		make_pipe(sentence);
	if (redirections(sentence, command) == ERROR)
		return (ERROR);
	is_valid_cmd(sentence);
	execute_cmds(command, sentence, has_pipe);
	current_node = sentence;
	wait_cmds(current_node);
	update_status(current_node);
	return (NO_ERROR);
}

void	execute_cmds(t_command *command, t_node *sentence, int has_pipe)
{
	t_node	*current_node;

	current_node = sentence;
	while (current_node)
	{
		if (current_node->token != NULL)
		{
			if (!has_pipe)
				run_simple_commands(command, current_node);
			else
				pipe_execution(command, current_node);
		}
		close_node_fds(sentence);
		current_node = current_node->next;
	}
	current_node = sentence;
	close_all_node_fds(current_node);
}

void	run_simple_commands(t_command *command, t_node *node)
{
	t_node	*current_node;

	current_node = node;
	if (current_node->token->type == BUILTIN)
		run_builtin(command, current_node, command->my_env, current_node->fd_out);
	else
		run_execve(command, current_node);
}

void	wait_cmds(t_node *node)
{
	t_node	*current_node;

	current_node = node;
	while (current_node)
	{
		if (current_node->pid != 0)
			waitpid(current_node->pid, &current_node->exit_status, 0);
		current_node = current_node->next;
	}
}

void	update_status(t_node *sentence)
{
	t_node		*node;

	node = sentence;
	if (g_status(-1) == 130 && g_flag == 130)
	{
		g_flag = 0;
		return ;
	}
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
