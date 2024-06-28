/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_last_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:03:06 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/06/28 12:59:02 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "listlib.h"

struct s_node	*create_last_node(char	*c, struct s_node *temp)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	temp->next = new;
	new->key = my_strcdup(c, '=');
	new->value = fromstrcdup(c, '=');
	new->next = NULL;
	return (new);
}
