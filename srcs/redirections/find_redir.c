/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 23:51:30 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/23 17:18:42 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirections(t_node *sentence)
{
	t_node		*temp;
	t_tokens	*word;
	int			ret;

	temp = sentence;
	ret = NO_ERROR;
	while (temp)
	{
		word = temp->token;
		while (word)
		{
			if (word->type == REDIR_APPEND)
				ret = do_append(temp, word);
			else if (word->type == REDIR_OUT)
				ret = do_redit_out(temp, word);
			else if (word->type == REDIR_IN)
				ret = do_redit_in(temp, word);
			if (ret == ERROR)
				return (ERROR);
			word = word->next;
		}
		temp = temp->next;
	}
	return (ret);
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
			{
				if (do_heredoc(temp, word) == ERROR)
					return (ERROR);
			}
			word = word->next;
		}
		temp = temp->next;
	}
	return (NO_ERROR);
}
