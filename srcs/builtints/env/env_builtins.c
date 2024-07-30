/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:18:34 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/07/29 22:01:20 by lpaixao-         ###   ########.fr       */
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
	char	*str;

	if (!name)
	{
		print_env_for_export(command->my_env);
		return ;
	}
	str = my_getenv_by_list(name, command->my_env);
	if (str != NULL)
		printf("Já existe essa variável - Mudar ela\n");
		//change_ev();
	else
		printf("Ainda não existe essa variável - Criar ela\n");
		//create_ev();
}

//unset
void	my_unset(char *name, t_command *command)
{
	char	*str;

	if (!name)
		return ;
	str = my_getenv_by_list(name, command->my_env);
	if (str != NULL)
		printf("Remover essa variável\n");
		//remove_ev(str, command);
}

void	print_env_for_export(t_node *list)
{
	t_node	*temp;

	temp = list;
	while (temp)
	{
		my_printf("declare -x %s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}

char	*my_getenv_by_list(const char *name, t_node *my_env)
{
	t_node	*temp;
	int		size_key;

	temp = my_env;
	while (temp)
	{
		size_key = my_strlen(temp->key);
		if (my_strncmp(name, temp->key, size_key) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}
