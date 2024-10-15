/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 00:53:01 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/10/15 00:36:54 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief create_heredoc_list - Creates a linked list of tokens from a heredoc
 * string.
 *
 * This function takes a string containing a heredoc and splits it into
 * individual tokens based on spaces. It initializes the first token and
 * subsequently adds more tokens to the linked list. The resulting linked
 * list of tokens can be used to represent the command input for the minishell.
 *
 * @param s: The input string representing the heredoc content to be tokenized.
 *
 * @return t_tokens*: Returns a pointer to the head of the linked list of tokens.
 *                   If memory allocation fails or if there are issues in
 *                   creating tokens, it returns NULL.
 *
 * @note This function is responsible for allocating memory for the token nodes.
 *       It also cleans up any allocated memory for the token list and the
 *       sentence array if an error occurs during the creation of tokens.
 */

t_tokens	*create_heredoc_list(char *s)
{
	t_tokens	*node;
	t_tokens	*temp;
	char		**sentence;
	int			i;

	i = 0;
	sentence = split_sentence_by_char(s, ' ');
	node = (t_tokens *)malloc(sizeof(t_tokens));
	if (!(node))
		return (free_sentences(sentence), NULL);
	temp = node;
	create_first_input_token(sentence[i], temp);
	if (sentence[i] == NULL)
		return (node);
	while (sentence[++i])
	{
		temp = create_last_token(sentence[i], temp);
		if (!temp)
			return (free_tokens(node), free_sentences(sentence), NULL);
	}
	my_clean_vect(sentence);
	return (node);
}
