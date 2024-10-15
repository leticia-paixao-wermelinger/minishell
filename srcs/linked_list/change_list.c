/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 22:18:49 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/10/14 23:19:11 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	remove_empty_tokens_in_sentence(t_tokens **first, \
		t_tokens *tword, t_node *sentence);

/**
 * @brief remove_env - Removes an environment variable node from the linked list.
 *
 * This function traverses the linked list of environment variables
 * to find and remove a specified node. It updates the pointers in the
 * previous node to bypass the removed node and frees the allocated memory
 * for the key and value of the environment variable.
 *
 * @param node: The environment variable node to be removed.
 * @param start: The head of the environment variable linked list.
 *
 * @return void: This function does not return a value.
 */

void	remove_env(t_env *node, t_env *start)
{
	t_env	*temp;

	temp = start;
	while (temp)
	{
		if (temp->next == node)
		{
			temp->next = node->next;
			free(node->key);
			free(node->value);
			free(node);
		}
		else
			temp = temp->next;
	}
}

/**
 * @brief remove_first_word_token - Removes the first token word from a command.
 *
 * This function removes the first token from the linked list of tokens
 * in a command. It updates the sentence to point to the next token
 * in the list and frees the memory allocated for the removed token's
 * word and the token itself.
 *
 * @param start: The first token in the linked list to be removed.
 * @param sentence: The current command node whose token list will be updated.
 *
 * @return void: This function does not return a value.
 */

void	remove_first_word_token(t_tokens *start, t_node *sentence)
{
	sentence->token = start->next;
	free(start->word);
	free(start);
	if (!(sentence->token))
		sentence->token = NULL;
}

/**
 * @brief remove_word_token - Removes a specified token word from the linked
 * list.
 *
 * This function removes a specific token from the linked list of tokens
 * associated with a command. It handles both the case where the token is
 * the first in the list and where it is elsewhere. The function frees the
 * memory allocated for the word and the token itself.
 *
 * @param node: The token node to be removed.
 * @param start: The head of the token linked list.
 * @param sentence: The current command node whose token list will be updated.
 *
 * @return void: This function does not return a value.
 */

void	remove_word_token(t_tokens *node, t_tokens *start, t_node *sentence)
{
	t_tokens	*temp;

	temp = start;
	if (start == node)
		return (remove_first_word_token(start, sentence));
	while (temp)
	{
		if (temp->next == node)
		{
			if (temp->next)
				temp->next = node->next;
			else
				temp->next = NULL;
			free(node->word);
			node->word = NULL;
			free(node);
			node = NULL;
			break ;
		}
		else
			temp = temp->next;
	}
	if (!start)
		sentence->token = NULL;
}

/**
 * @brief remove_empty_nodes - Removes empty token nodes from the command list.
 *
 * This function traverses each command in the linked list of commands
 * and removes any tokens that are empty (i.e., have a length of 0).
 * It checks both the first token and subsequent tokens, ensuring that
 * the command structure remains valid after removal.
 *
 * @param main_node: The head of the linked list of command nodes.
 *
 * @return void: This function does not return a value.
 */

void	remove_empty_nodes(t_node *main_node)
{
	t_node		*sentence;
	t_tokens	*first;
	t_tokens	*tword;

	sentence = main_node;
	while (sentence)
	{
		first = sentence->token;
		tword = first;
		remove_empty_tokens_in_sentence(&first, tword, sentence);
		if (!first)
			sentence->token = NULL;
		sentence = sentence->next;
	}
}

static void	remove_empty_tokens_in_sentence(t_tokens **first, \
		t_tokens *tword, t_node *sentence)
{
	t_tokens	*temp;

	while (*first && my_strlen((*first)->word) == 0)
	{
		temp = (*first)->next;
		remove_word_token(tword, *first, sentence);
		tword = temp;
		*first = temp;
		sentence->token = *first;
	}
	while (tword)
	{
		if (tword->next != NULL)
		{
			if (my_strlen(tword->next->word) == 0)
				remove_word_token(tword->next, *first, sentence);
			else
				tword = tword->next;
		}
		else
			break ;
	}
}
