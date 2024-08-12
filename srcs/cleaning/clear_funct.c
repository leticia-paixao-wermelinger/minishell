/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_funct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:06:32 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/07/26 22:56:54 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	clear_input(t_command *command)
{
	free(command->prompt);
	free(command->input);
	free_list(command->l_input);
}

void	clear_all(t_command *command)
{
	clear_input(command);
	rl_clear_history();
//	free(command->prompt);
//	free(command->invalid_metas);
	free_node(command->my_env);
	printf("Exiting...\n");
}

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

void	free_node(t_env *list)
{
	t_env	*temp;
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