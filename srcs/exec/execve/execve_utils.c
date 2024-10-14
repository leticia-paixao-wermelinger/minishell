/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:46:24 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/09 16:27:57 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	env_list_size(t_env *list)
{
	int	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

int	count_tokens_in_node(t_node *sentence)
{
	int			i;
	t_node		*node;
	t_tokens	*current_token;

	i = 0;
	node = sentence;
	while (node)
	{
		current_token = node->token;
		while (current_token)
		{
			i++;
			current_token = current_token->next;
		}
		node = node->next;
	}
	return (i);
}
