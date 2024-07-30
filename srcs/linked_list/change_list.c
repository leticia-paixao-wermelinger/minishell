/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 22:18:49 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/07/29 23:51:45 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    change_value(t_node *node, char *str)
{
	free(node->value);
	node->value = my_strdup(str);
}

void	create_new_ev(char *str, t_node *env_list)
{
	t_node	*temp;

	temp = env_list;
	while (temp)
	{
		if (temp->next == NULL)
		{
			create_last_env_node(str, temp);
			return ;
		}
		temp = temp->next;
	}
}

void	remove_node(t_node *node, t_node *start)
{
	t_node	*temp;

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

