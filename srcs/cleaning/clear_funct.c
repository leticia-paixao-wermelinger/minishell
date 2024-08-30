/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_funct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:06:32 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/08/29 15:50:04 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	clear_loop_end(t_command *command)
{
	clear_input(command);
	free_list(command->l_input);
}

void	clear_input(t_command *command)
{
	free(command->prompt);
	free(command->input);
}

void	final_clear(t_command *command)
{
	clear_history(); //n esquecer de alterar depois p/ rl_clear_history();
	free_env(command->my_env);
	printf("Exiting...\n");
}

void	free_list(t_node *list)
{
	t_node	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		free(temp);
	}
}

void	free_env(t_env *list)
{
	t_env	*temp;

	while (list)
	{
		temp = list;
		free(temp->key);
		free(temp->value);
		list = list->next;
		free(temp);
	}
}
