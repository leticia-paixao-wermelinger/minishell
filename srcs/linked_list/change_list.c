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
//	printf("Entereço do q deve ser o novo head da lista = %p, com %s\n", start->next, start->next->word);
	sentence->token = start->next;
	free(start->word);
	free(start);
	if (!(sentence->token))
		sentence->token = NULL;
//	printf("Endereço do novo head da lista: %p, com %s\n", sentence->token, sentence->token->word);
}

void	remove_word_token(t_tokens *node, t_tokens *start, t_node *sentence)
{
	t_tokens *temp;

	temp = start;
//	printf("--------REMOÇÃO DE NODE:----------\n");
//	printf("start = %p, com %s\n", start, start->word);
//	printf("node = %p, com %s\n", node, node->word);
	if (start == node)
	{
//		printf("start = node\n");
		remove_first_word_token(start, sentence);
		return ;
	}
	while (temp)
	{
//		printf("No loop: temp = %p\n", temp);
		if (temp->next == node)
		{
//			printf("Está no if de temp->next = node, com next = %p\n", temp->next);
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
	{
//		printf("Entrou no if de word não existe, da linha 73\n");
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