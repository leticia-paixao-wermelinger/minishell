/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 00:53:01 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/26 01:51:41 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tokens	*create_heredoc_list(char *s)
{
	t_tokens	*node;
	t_tokens	*temp;
	char	    **sentence;
	int			i;

	i = 0;
	sentence = split_sentence_by_char(s, ' ');
	node = (t_tokens *)malloc(sizeof(t_tokens));
	if (!(node))
	{
		free_sentences(sentence);
		return (NULL);
	}
	temp = node;
	create_first_input_token(sentence[i], temp);
	if (sentence[i] == NULL)
		return (node);
	while (sentence[++i])
	{
		temp = create_last_token(sentence[i], temp);
		if (!temp)
		{
			free_sentences(sentence);
			free_tokens(node);
			return (NULL);
		}
	}
	my_clean_vect(sentence);
	return (node);
}