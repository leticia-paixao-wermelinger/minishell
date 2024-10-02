/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 22:18:49 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/24 14:22:23 by lpaixao-         ###   ########.fr       */
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

void	remove_first_word_token(t_tokens *start)
{
	t_tokens *temp;

	printf("Entrou na remove_first_word_token: |%s| &%p\n", start->word, start);
	temp = start;
	start = start->next;
	free(temp->word);
	free(temp);
}

void	remove_word_token(t_tokens *node, t_tokens *start)
{
	t_tokens *temp;

	temp = start;
	printf("Entrou na remove_word_token: |%s| &%p\n", node->word, node);
	if (start == node)
	{
		remove_first_word_token(start);
		return ;
	}
	while (temp)
	{
	//	printf("Está no loop de remove_word_token em %s e c o next = %s\n", temp->word, temp->next->word);
		if (temp->next == node)
		{
			printf("Vai apagar: |%s| &%p\n", node->word, node);
			temp->next = node->next;
			free(node->word);
			free(node);
			break ;
		}
		else
			temp = temp->next;
	}
}
