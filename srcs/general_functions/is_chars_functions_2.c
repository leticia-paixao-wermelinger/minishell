/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_chars_functions_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:36:37 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/18 17:18:19 by lraggio          ###   ########.fr       */
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
/*
int	is_file(t_node *node, t_node *list)
{
	t_node	*temp;

	temp = list;
	while (temp)
	{
		if (temp->next == node && is_redirect(temp->token) == TRUE)
			return (TRUE);
		temp = temp->next;
	}
	return (FALSE);
}*/

int	is_redirect(char *str)
{
	if (my_strcmp(str, ">>") == 0 || my_strcmp(str, "<<") == 0)
		return (TRUE);
	else if (my_strcmp(str, ">") == 0 || my_strcmp(str, "<") == 0)
		return (TRUE);
	return (FALSE);
}

/*
int	is_redirect(int n)
{
	if (n == REDIR_APPEND || n == REDIR_HEREDOC)
		return (TRUE);
	else if (n == REDIR_OUT || n == REDIR_IN)
		return (TRUE);
	return (FALSE);
}*/
