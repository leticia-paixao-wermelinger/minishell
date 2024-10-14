/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 20:37:50 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/10/14 19:49:28 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	input_ends_with_redir(char *str)
{
	int	i;

	i = my_strlen(str);
	while (--i >= 0)
	{
		if (str[i] != SPACE_CHAR && str[i] != LESS_THAN
			&& str[i] != GREATER_THAN)
			return (NO_ERROR);
		else if (str[i] == LESS_THAN || str[i] == GREATER_THAN)
			break ;
	}
	print_error("minishell: syntax error near unexpected token `newline'\n");
	g_status(MISUSE);
	return (ERROR);
}

int	check_following_redirs(t_tokens *node)
{
	t_tokens	*next;

	next = node->next;
	if (token_is_redir(node) == TRUE && token_is_redir(next) == TRUE)
		return (redir_syntax_error(next->type));
	return (NO_ERROR);
}
