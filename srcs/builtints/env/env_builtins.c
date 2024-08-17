/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:18:34 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/08/17 15:11:07 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

//static void	conditions_to_export(char **str, char **end_str);

void	print_env(t_env *list)
{
	t_env	*temp;

	temp = list;
	while (temp)
	{
		my_printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}

//export

void	my_export(t_env *env, t_node *node_i)
{
	int		i;
	char	*str;
	t_env	*node_env;

	printf("ENTROU NA MY_EXPORT	\n");
	i = 0;
	str = NULL;
	node_env = NULL;
	if (!node_i->value[1])
	{
		printf("Entrou na condição de export sem parametro\n");
		print_env_for_export(env);
		return ;
	}
	while (node_i->value[++i])
	{
		printf("Está no while da matriz da sentença do export no índice %i\n", i);
		if (is_valid_ev(node_i->value[i]) == ERROR)
		{
			printf("value[%i] = |%s|: nome é inválido\n", i, node_i->value[i]);
			continue ;
		}
		else
		{
			printf("value[%i] = |%s|: nome é válido\n", i, node_i->value[i]);
			node_env = my_getenv_by_list(node_i->value[i], env);
			str = fromstrcdup(node_i->value[i], '=');
			if (node_env != NULL)
				change_env_value(node_env, str);
			else
				create_new_ev(node_i->value[i], env);
			free(str);
		}
	}
}

/*
void	my_export(char **str, t_command *command)
{
	t_env	*node;
	char	*new_value;
	char	*end_str;

	if (!*str)
	{
		print_env_for_export(command->my_env);
		return ;
	}
	new_value = NULL;
	end_str = fromstrcdup(*str, '=');
	node = my_getenv_by_list(*str, command->my_env);
	conditions_to_export(str, &end_str);
	if (is_closed_by_quot_marks(end_str) != TRUE)
		new_value = fromstrcdup(*str, '=');
	else
		new_value = my_strdup(*str);
	if (node != NULL)
		change_env_value(node, new_value);
	else
		create_new_ev(*str, command->my_env);
	free(new_value);
	free(end_str);
}

static void	conditions_to_export(char **str, char **end_str)
{
	char	*str2;

	str2 = NULL;
		if (is_closed_by_quot_marks(*end_str) == TRUE)
	{
		str2 = validate_quot_marks_for_export(*end_str);
		free(*str);
		*str = my_strdup(str2);
		free(str2);
	}
	else if (is_there_space(*str) == TRUE)
	{
		str2 = my_strcdup(*str, SPACE_CHAR);
		free(*str);
		*str = my_strdup(str2);
		free(str2);
	}
}*/

// unset

void	my_unset(t_env *env, t_node *node_i)
{
	t_env	*node_env;
	int		i;

	i = 1;
	node_env = NULL;
	while (node_i->value[i])
	{
		if (!node_i->value[i])
		{
			i++;
			continue ;
		}
		node_env = my_getenv_by_list(node_i->value[i], env);
		if (node_env != NULL)
			remove_env(node_env, env);
		i++;
	}
}
