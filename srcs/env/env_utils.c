/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:27:14 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/27 19:16:03 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void change_sh_level(t_env *node);

void	get_env(t_command *command)
{
	extern char	**environ;
	t_env		*temp;
	int			i;
	int			j;

	i = 0;
	j = 0;
	command->my_env = NULL;
	while (environ[i])
		i++;
	command->my_env = create_first_env_node(environ[j], command->my_env);
	temp = command->my_env;
	while (++j < i)
		temp = create_last_env_node(environ[j], temp);
	change_sh_level(command->my_env);
}

t_env	*my_getenv_by_list(const char *name, t_env *my_env)
{
	t_env	*temp;
	int		size_key;

	temp = my_env;
	while (temp)
	{
		size_key = my_strlen(temp->key);
		if (my_strncmp(name, temp->key, size_key) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

static void	change_sh_level(t_env *node) // TESTAR JUNTO COM A EXECUÇÃO
{
	t_env	*level;
	int		number;

	level = NULL;
	level = my_getenv_by_list("SHLVL", node);
	number = my_atoi(level->value) + 1;
	free(level->value);
	level->value = my_itoa(number);
}
