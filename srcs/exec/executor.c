/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:27:09 by lraggio           #+#    #+#             */
/*   Updated: 2024/09/30 00:24:44 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int executor(t_command *command, t_node *sentence)
{
	t_env	*env;
	t_node	*current_node;

	if (is_there_space(sentence->token->word))
		return (print_cmd_not_found(sentence), NO_ERROR);
	if (has_pipe_or_not(sentence) == TRUE)
		make_pipe(sentence);
	if (has_redirect(sentence) == TRUE)
		printf("Tem redirect!\n");
		//if (redirections(sentence, env, command) == ERROR)
			return (ERROR);
	current_node = sentence;
	while (current_node)
	{
		if (!current_node->next)
			run_simple_commands(command, current_node);
		else
			pipe_execution(command, current_node);
		close_node_fds(current_node);
		current_node = current_node->next;
	}
	current_node = sentence;
	wait_cmds(current_node);
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
