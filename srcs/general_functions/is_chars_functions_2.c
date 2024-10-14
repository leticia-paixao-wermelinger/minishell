/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_chars_functions_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:36:37 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/21 22:33:06 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redir_out(char *s)
{
	if (my_strcmp(s, ">") == 0)
		return (TRUE);
	return (FALSE);
}

int	is_redir_in(char *s)
{
	if (my_strcmp(s, "<") == 0)
		return (TRUE);
	return (FALSE);
}

int	is_heredoc(char *s)
{
	if (my_strcmp(s, "<<") == 0)
		return (TRUE);
	return (FALSE);
}

int	is_redirect(char *str)
{
	if (my_strcmp(str, ">>") == 0 || my_strcmp(str, "<<") == 0)
		return (TRUE);
	else if (my_strcmp(str, ">") == 0 || my_strcmp(str, "<") == 0)
		return (TRUE);
	return (FALSE);
}

int	token_is_redir(t_tokens *node)
{
	if (node->type == REDIR_APPEND || node->type == REDIR_HEREDOC)
		return (TRUE);
	else if (node->type == REDIR_OUT || node->type == REDIR_IN)
		return (TRUE);
	return (FALSE);
}