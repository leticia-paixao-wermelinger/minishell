/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:18:34 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/07/29 23:41:09 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

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

void	my_export(char *name, t_command *command)
{
	t_node	*node;
	char	*new_value;

	if (!name)
	{
		print_env_for_export(command->my_env);
		return ;
	}
//VALIDAR ERRO! Se não tiver no formato VARIAVEL=value tem que dar erro!
	node = my_getenv_by_list(name, command->my_env);
	new_value = fromstrcdup(name, '=');
	if (node != NULL)
		change_value(node, new_value);
	else
		create_new_ev(name, command->my_env);
	free(new_value);
}

void	my_unset(char *name, t_command *command)
{
	t_node	*node;

	if (!name)
		return ;
	node = my_getenv_by_list(name, command->my_env);
	if (node != NULL)
		remove_node(node, command->my_env);
}
