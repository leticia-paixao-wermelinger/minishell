/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:17:58 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/06/28 19:42:01 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_first_node(char *c, t_node *list)
{
	list = (t_node *)malloc(sizeof(t_node));
	list->key = my_strcdup(c, '=');
	list->value = fromstrcdup(c, '=');
	list->next = NULL;
	return (list);
}

t_node	*create_last_node(char	*c, t_node *prev)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	prev->next = new;
	new->key = my_strcdup(c, '=');
	new->value = fromstrcdup(c, '=');
	new->next = NULL;
	return (new);
}

void	print_env(t_node *list)
{
	t_node	*temp;

	temp = list;
	while (temp)
	{
		my_printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}
