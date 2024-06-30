/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:18:34 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/06/30 19:08:37 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

//export

//enset

char	*my_getenv_by_list(const char *name, t_node *my_env)
{
	t_node	*temp;

	temp = my_env;
	while (temp)
	{
		if (my_strcmp(name, temp->key) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}
