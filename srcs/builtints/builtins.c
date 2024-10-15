/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 22:13:01 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/10/14 23:38:16 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	run_builtin(t_command *command, t_node *node, t_env *env, int fd)
{
	int			ret;

	ret = NO_ERROR;
	if (my_strcmp(node->token->word, "echo") == 0)
		ret = my_echo(node->token->next, fd);
	else if (my_strcmp(node->token->word, "cd") == 0)
		ret = my_cd(node->token->next, env);
	else if (my_strcmp(node->token->word, "pwd") == 0)
		ret = pwd();
	else if (my_strcmp(node->token->word, "export") == 0)
		my_export(env, node->token->next, fd);
	else if (my_strcmp(node->token->word, "unset") == 0)
		my_unset(env, node->token->next);
	else if (my_strcmp(node->token->word, "env") == 0)
		print_env(env, fd);
	else if (my_strcmp(node->token->word, "exit") == 0)
		ret = my_exit(node->token->next, command);
	node->exit_status = ret;
	return (ret);
}
