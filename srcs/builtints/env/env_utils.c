/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:32:50 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/07/03 15:05:50 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	get_env(t_command *command)
{
	extern char	**environ;
	t_node		*temp;
	int			i;
	int			j;

	i = 0;
	j = 0;
	command->my_env = NULL;
	while (environ[i])
		i++;
	command->my_env = create_first_node(environ[j], command->my_env);
	temp = command->my_env;
	while (++j < i)
		temp = create_last_node(environ[j], temp);
}
