/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_funct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:06:32 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/02 00:56:53 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	clear_loop_end(t_command *command)
{
	free_list(command->l_input);
	clear_input(command);
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
	t_node		*temp;
	t_node		*next_node;
	t_tokens	*temp_token;
	t_tokens	*next_token;

	while (list)
	{
		temp = list;
		temp_token = temp->token;
		while (temp_token)
		{
			next_token = temp_token->next;
			free(temp_token->word);
			free(temp_token);
			temp_token = next_token;
		}
		next_node = list->next;
		free(temp);
		list = next_node;
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
