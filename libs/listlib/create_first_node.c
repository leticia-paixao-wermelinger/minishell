/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_first_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:56:06 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/06/28 12:57:48 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "listlib.h"

struct s_node	*create_first_node(char *c, struct s_node *list)
{
	list = (t_node *)malloc(sizeof(t_node));
	list->key = my_strcdup(c, '=');
	list->value = fromstrcdup(c, '=');
	list->next = NULL;
	return (list);
}
