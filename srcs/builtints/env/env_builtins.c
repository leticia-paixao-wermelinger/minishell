/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:18:34 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/10/09 16:20:28 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	print_env(t_env *list, int fd)
{
	t_env	*temp;

	temp = list;
	while (temp)
	{
		my_putstr_fd(temp->key, fd);
		my_putstr_fd("=", fd);
		my_putstr_fd(temp->value, fd);
		my_putstr_fd("\n", fd);
		temp = temp->next;
	}
}

void	my_export(t_env *env, t_tokens *node_t, int fd)
{
	char		*str;
	t_env		*node_env;
	t_tokens	*temp;

	str = NULL;
	node_env = NULL;
	temp = node_t;
	if (node_t == NULL)
	{
		print_env_for_export(env, fd);
		return ;
	}
	while (temp)
	{
		if (is_valid_ev(temp->word) == ERROR)
		{
			temp = temp->next;
			continue ;
		}
		else
		{
			node_env = my_getenv_by_list(temp->word, env);
			str = fromstrcdup(temp->word, '=');
			if (node_env != NULL)
				change_env_value(node_env, str);
			else
				create_new_ev(temp->word, env);
			free(str);
		}
		temp = temp->next;
	}
}

void	my_unset(t_env *env, t_tokens *node_i)
{
	t_env		*node_env;
	t_tokens	*temp;

	temp = node_i;
	node_env = NULL;
	while (temp)
	{
		if (!temp->word)
		{
			temp = temp->next;
			continue ;
		}
		node_env = my_getenv_by_list(temp->word, env);
		if (node_env != NULL)
			remove_env(node_env, env);
		temp = temp->next;
	}
}
