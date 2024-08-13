/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_chars_functions_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:36:37 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/08/12 21:43:49 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

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
}

int	is_redirect(int n)
{
	if (n == REDIR_APPEND || n == REDIR_HEREDOC)
		return (TRUE);
	else if (n == REDIR_OUT || n == REDIR_IN)
		return (TRUE);
	return (FALSE);
}
