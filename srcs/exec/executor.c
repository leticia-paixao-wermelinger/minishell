/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:27:09 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/07 22:21:09 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_cmds(t_node *sentence)
{
	while (sentence->token == NULL) //pro caso $nao_existo
	{
		if (sentence->next)
			sentence = sentence->next;
		else
			return (close_node_fds(sentence), ERROR);
	}
	if (is_there_space(sentence->token->word))
		print_errno(sentence);
	return (NO_ERROR);
}

int executor(t_command *command, t_node *sentence)
{
	t_node	*current_node;
	int	has_pipe;

	if (check_cmds(command->l_input) == ERROR)
		return (ERROR);
	has_pipe = has_pipe_or_not(sentence);
	if (has_pipe == TRUE)
		make_pipe(sentence);
	if (redirections(sentence, command) == ERROR)
		return (ERROR);
	if (check_cmds(sentence) == ERROR)
		return (ERROR);
	current_node = sentence;
	while (current_node)
	{
		if (!has_pipe)
			run_simple_commands(command, current_node);
		else
			pipe_execution(command, current_node);
		close_node_fds(current_node);
		current_node = current_node->next;
	}
	current_node = sentence;
	wait_cmds(current_node);
	close_all_node_fds(current_node);
	update_status(sentence);
    return (NO_ERROR);
}

void	run_simple_commands(t_command *command, t_node *node)
{
	t_node	*current_node;

	current_node = node;
	if (current_node->token->type == BUILTIN)
		run_builtin(command, current_node->token, command->my_env, current_node->fd_out);
	else
		run_execve(command, current_node);
}
