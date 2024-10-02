/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 00:36:05 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/26 00:48:24 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * make_list_from_input - Creates a linked list of input nodes from the input matrix.
 * 
 * This function iterates through the input matrix and creates a linked list 
 * of nodes, each representing a part of the command input. The first node is 
 * initialized, and subsequent nodes are added to the list.
 *
 * @param command: A pointer to the t_command structure that contains the 
 * input matrix and the head of the linked list (l_input).
 *
 * @return void: This function does not return a value.
 */

void	make_list_from_input(t_command *command)
{
	int			i;
	t_node		*temp_sentence;

	i = 0;
	command->l_input = create_first_input_node(command->input_matrix[i], command->l_input);
	temp_sentence = command->l_input;
	while (command->input_matrix[++i])
		temp_sentence = create_last_input_node(command->input_matrix[i], temp_sentence);
}

/**
 * make_list_tokens - Creates a list of tokens from a given string and attaches it to a node.
 * 
 * This function takes a string (s) and splits it into individual words (tokens) 
 * based on spaces. For each word, it creates a `t_tokens` structure, which represents 
 * a token in the command, storing the word and its type. The first token is initialized 
 * and added to the `token` field of the `t_node` structure provided in the `list` parameter.
 * Subsequent tokens are created and linked together in a singly linked list.
 *
 * The function performs memory allocation for each token. If at any point the memory 
 * allocation fails, it frees all previously allocated tokens and returns NULL. 
 * Otherwise, it returns a pointer to the head of the token list.
 *
 * @param s: The input string to be tokenized. This string is expected to represent 
 *           part of the user’s command, and each word in the string will be treated 
 *           as a separate token.
 * 
 * @param list: A pointer to the `t_node` structure where the token list will be 
 *              stored. The tokens will be attached to the `token` field of this node.
 *
 * @return t_tokens*: A pointer to the head of the token list (the first token), 
 *                    or NULL if a memory allocation error occurs.
 */

t_tokens	*make_list_tokens(char *s, t_node *list)
{
	t_tokens	*temp_word;
	char	    **sentence;
	int			i;

	i = 0;
	sentence = split_sentence_by_char(s, ' ');
	list->token = (t_tokens *)malloc(sizeof(t_tokens));
	if (!(list->token))
	{
		free_sentences(sentence);
		free(list);
		return (NULL);
	}
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
			free(list);
			list = NULL;
			return (NULL);
		}
	}
	free_sentences(sentence);
	return (list->token);
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
		return;
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
