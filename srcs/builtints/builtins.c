/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 22:13:01 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/18 17:18:19 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	run_builtin(t_command *command, t_tokens *token, t_env *env, int fd)
{
	int			ret;

	ret = NO_ERROR;
	if (my_strcmp(token->word, "echo") == 0)
		my_echo(token->next, fd);
	else if (my_strcmp(token->word, "cd") == 0)
		ret = my_cd(token->next, env);
	else if (my_strcmp(token->word, "pwd") == 0)
		ret = pwd();
	else if (my_strcmp(token->word, "export") == 0)
		my_export(env, token->next, fd);
	else if (my_strcmp(token->word, "unset") == 0)
		my_unset(env, token->next);
	else if (my_strcmp(token->word, "env") == 0)
		print_env(env, fd);
	else if (my_strcmp(token->word, "exit") == 0)
		ret = my_exit(token->next, command); // Em construção!
	return (ret);
}
