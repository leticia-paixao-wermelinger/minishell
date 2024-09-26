/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 23:51:30 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/26 09:42:36 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirections(t_node *sentence, t_env *env)
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
			if (word->next != NULL)
			{
				if (word->next->type == REDIR_APPEND)
					ret = do_append(temp, word->next);
				else if (word->next->type == REDIR_OUT)
					ret = do_redir_out(temp, word->next);
				else if (word->next->type == REDIR_IN)
					ret = do_redir_in(temp, word->next);
				else if (word->next->type == REDIR_HEREDOC)
					ret = do_heredoc(temp, word->next, env);
			}
			if (ret == ERROR)
				return (ERROR);
			word = word->next;
		}
		temp = temp->next;
	}
	return (ret);
}
/*
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
			if (word->next != NULL)
			{
				if (word->next->type == REDIR_HEREDOC)
				{
					if (do_heredoc(temp, word->next) == ERROR)
						return (ERROR);
				}
			}
			word = word->next;
		}
		temp = temp->next;
	}
	return (NO_ERROR);
}*/
