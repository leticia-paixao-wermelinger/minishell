/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_funct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:06:32 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/10/09 20:11:34 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clear_loop_end(t_command *command)
{
	free_list(command->l_input);
	clear_input(command);
}

void	clear_input(t_command *command)
{
	free(command->prompt);
	free(command->input);
	if (command->input_matrix != NULL)
		my_clean_vect(command->input_matrix);
}

void	final_clear(t_command *command)
{
	clear_history(); //n esquecer de alterar depois p/ rl_clear_history();
	free_env(command->my_env);
}

void	free_list(t_node *list)
{
	t_node		*temp;
	t_node		*next_node;
	t_tokens	*temp_token;

	while (list)
	{
		temp = list;
		temp_token = temp->token;
		free_t_tokens(temp_token);
		next_node = list->next;
		free(temp);
		temp = NULL;
		list = next_node;
	}
}

void	free_t_tokens(t_tokens *node)
{
	t_tokens	*next_token;

	next_token = NULL;
	while (node)
	{
		next_token = node->next;
		free(node->word);
		node->word = NULL;
		free(node);
		node = NULL;
		node = next_token;
	}
}

void	free_env(t_env *list)
{
	t_env	*temp;

	while (list)
	{
		temp = list;
		free(temp->key);
		temp->key = NULL;
		free(temp->value);
		temp->value = NULL;
		list = list->next;
		free(temp);
		temp = NULL;
	}
}
