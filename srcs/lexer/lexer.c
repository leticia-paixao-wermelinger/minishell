/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:27:15 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/07/26 20:47:47 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	lexer(t_command *command)
{
	t_node	*list;

	list = command->l_input;
	while (list)
	{
		set_token(list, command->l_input);
		list = list->next;
	}
}

void	set_token(t_node *node, t_node *first)
{
	if (is_builtin(node->value) == TRUE)
		node->token = BUILTIN;
	else if (is_pipe(node->value) == TRUE)
		node->token = T_PIPE;
	else if (is_append(node->value) == TRUE)
		node->token = REDIR_APPEND;
	else if (is_redir_out(node->value) == TRUE)
		node->token = REDIR_OUT;
	else if (is_redir_in(node->value) == TRUE)
		node->token = REDIR_IN;
	else if (is_heredoc(node->value) == TRUE)
		node->token = REDIR_HEREDOC;
	else if (is_file(node, first) == TRUE)
		node->token = MY_FILE;
	else
		node->token = EXEC;
}
