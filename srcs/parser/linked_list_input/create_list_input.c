/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 00:36:05 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/10/14 23:42:19 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * @brief make_list_from_input - Creates a linked list of input nodes
 *                               from a matrix of input strings.
 *
 * This function initializes the linked list of input nodes (`l_input`)
 * in the provided `t_command` structure. Each input string in the
 * `input_matrix` is converted into a separate node in the linked list.
 *
 * @param command A pointer to the command structure containing
 *                the input matrix and a linked list of input nodes.
 */

void	make_list_from_input(t_command *command)
{
	int		i;
	t_node	*temp_sentence;

	i = 0;
	command->l_input = create_first_input_node(command->input_matrix[i],
			command->l_input);
	temp_sentence = command->l_input;
	while (command->input_matrix[++i])
		temp_sentence = create_last_input_node(command->input_matrix[i],
				temp_sentence);
}

/**
 * @brief make_list_tokens - Creates a linked list of tokens from a
 *                          given input string.
 *
 * This function initializes the linked list of tokens for a specific
 * input string (`s`). It splits the input string into words based on
 * spaces and creates tokens accordingly.
 *
 * @param s A pointer to the input string to be tokenized.
 * @param list A pointer to the node in the linked list where the
 *              tokens will be stored.
 * @return A pointer to the first token in the created list, or NULL
 *         if an error occurs during memory allocation.
 */

t_tokens	*make_list_tokens(char *s, t_node *list)
{
	t_tokens	*temp_word;
	char		**sentence;
	int			i;

	i = 0;
	sentence = split_sentence_by_char(s, ' ');
	list->token = (t_tokens *)malloc(sizeof(t_tokens));
	if (!(list->token))
		return (free_sentences(sentence), free(list), NULL);
	temp_word = list->token;
	create_first_input_token(sentence[i], temp_word);
	if (sentence[i] == NULL)
		return (list->token);
	while (sentence[++i])
	{
		temp_word = create_last_token(sentence[i], temp_word);
		if (!temp_word)
		{
			free_sentences(sentence);
			free_tokens(list->token);
			return (free(list), list = NULL, NULL);
		}
	}
	return (free_sentences(sentence), list->token);
}

/**
 * free_sentences - Frees a dynamically allocated array of strings.
 *
 * This function iterates through an array of strings and frees each one,
 * followed by freeing the array itself.
 *
 * @param sentences: A double pointer to the array of strings to be freed.
 *
 * @return void: This function does not return a value.
 */

void	free_sentences(char **sentences)
{
	int	i;

	i = 0;
	if (!sentences)
		return ;
	while (sentences[i])
	{
		free(sentences[i]);
		sentences[i] = NULL;
		i++;
	}
	free(sentences);
	sentences = NULL;
}

/**
 * free_tokens - Frees a linked list of tokens.
 *
 * This function iterates through a linked list of tokens, freeing each token's
 * word and the token structure itself.
 *
 * @param token: A pointer to the first token in the linked list to be freed.
 *
 * @return void: This function does not return a value.
 */

void	free_tokens(t_tokens *token)
{
	t_tokens	*temp;

	while (token)
	{
		temp = token->next;
		free(token->word);
		token->word = NULL;
		free(token);
		token = NULL;
		token = temp;
	}
}
