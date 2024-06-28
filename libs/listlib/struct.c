/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:38:01 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/03/27 16:28:51 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*declare_nodes(char	**str, t_node *list)
{
	int		i;
	t_node	*temp;

	temp = NULL;
	i = 1;
	list = declare_first_node(str[i], list);
	temp = list;
	i++;
	while (str[i])
	{
		temp = declare_last_node(str[i], temp);
		i++;
	}
	set_index(list);
	return (list);
}

t_node	*declare_first_node(char *c, t_node *list)
{
	list = (t_node *)malloc(sizeof(t_node));
	list->val = my_atoi(c);
	list->i = 0;
	list->next = NULL;
	return (list);
}

t_node	*declare_last_node(char	*c, t_node *temp)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	temp->next = new;
	new->val = my_atoi(c);
	new->i = 0;
	new->next = NULL;
	return (new);
}

void	set_index(t_node *list)
{
	t_node	*t1;
	t_node	*t2;

	t1 = list;
	t2 = NULL;
	while (t1)
	{
		t2 = t1;
		while (t2)
		{
			if (t1->val > t2->val)
				t1->i++;
			else
				t2->i++;
			t2 = t2->next;
		}
		t1 = t1->next;
	}
}
