/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:32:50 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/10/09 21:37:08 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	print_env_for_export(t_env *list, int fd)
{
	t_env	*temp;

	temp = list;
	while (temp)
	{
		my_putstr_fd("declare -x ", fd);
		my_putstr_fd(temp->key, fd);
		my_putstr_fd("=", fd);
		my_putstr_fd(temp->value, fd);
		my_putstr_fd("\n", fd);
		temp = temp->next;
	}
}

int	is_valid_ev(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '=' && is_valid_exp_char(str[0]) == TRUE)
	{
		while (str[i])
		{
			if (is_valid_exp_char(str[i]) == TRUE)
				i++;
			else if (str[i] == '=')
				break ;
			else
				return (ERROR);
		}
	}
	else
		return (ERROR);
	if (str[i] == '=')
		i++;
	else
		return (ERROR);
	return (NO_ERROR);
}

void	change_env_value(t_env *node, char *str)
{
	free(node->value);
	node->value = my_strdup(str);
}

void	create_new_ev(char *str, t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (temp->next == NULL)
		{
			create_last_env_node(str, temp);
			break ;
		}
		temp = temp->next;
	}
}
