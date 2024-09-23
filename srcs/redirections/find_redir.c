/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 23:51:30 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/23 00:11:43 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirections(t_node *sentence)
{
	t_node		*temp;
	t_tokens	*word;

	temp = sentence;
	while (temp)
	{
		word = temp->token;
		while (word)
		{
			if (word->type == REDIR_APPEND)
				do_append(temp, word);
			else if (word->type == REDIR_OUT)
				do_redit_out(temp, word);
			else if (word->type == REDIR_IN)
				do_redit_in(temp, word);
			word = word->next;
		}
		temp = temp->next;
	}
	return (NO_ERROR);
}

int	find_heredoc(t_node *sentence)
{
	t_node		*temp;
	t_tokens	*word;

	temp = sentence;
	while (temp)
	{
		word = temp->token;
		while (word)
		{
			if (word->type == REDIR_HEREDOC)
				do_heredoc(temp, word);
		}
		temp = temp->next;
	}
	return (NO_ERROR);
}
