/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_funct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:06:32 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/06/28 20:11:28 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_node *list)
{
	t_node	*temp;
	int		i;

	i = 1;
	while (list)
	{
		temp = list;
		free(temp->key);
		free(temp->value);
		list = list->next;
		free(temp);
		i++;
	}
}
