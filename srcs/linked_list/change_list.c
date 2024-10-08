/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 22:18:49 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/10/03 23:43:01 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	remove_first_word_token(t_tokens *start, t_node *sentence)
{
	t_tokens *temp;

	temp = start;
	start = start->next;
	free(temp->word);
	free(temp);
	if (!start)
		sentence->token = NULL;
}

void	remove_word_token(t_tokens *node, t_tokens *start, t_node *sentence)
{
	t_tokens *temp;

	temp = start;
	if (start == node)
	{
		remove_first_word_token(start, sentence);
		return ;
	}
	while (temp)
	{
		if (temp->next == node)
		{
			temp->next = node->next;
			free(node->word);
			free(node);
			break ;
		}
		else
			temp = temp->next;
	}
	if (!start)
	{
		printf("Entrou no if de word não existen da linha 73\n");
		sentence->token = NULL;
	}
}

void	remove_empty_nodes(t_node *main_node)
{
	t_node		*sentence;
	t_tokens	*first;
	t_tokens	*tword;
	t_tokens	*temp;

	sentence = main_node;
	while(sentence)
	{
		first = sentence->token;
		tword = first;
		while (first && my_strlen(first->word) == 0)
		{
			temp = first->next;
			remove_word_token(tword, first, sentence);
			tword = temp;
			first = temp;
			sentence->token = first;
		}
		while(tword)
		{
			if (tword->next != NULL)
			{
				if (my_strlen(tword->next->word) == 0)
					remove_word_token(tword->next, first, sentence);
				else
					tword = tword->next;
			}
			else
				break ;
		}
		if (!first)
			sentence->token = NULL;
		sentence = sentence->next;
	}
}