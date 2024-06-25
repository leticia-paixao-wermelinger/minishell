/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declate_structs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:32:50 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/06/25 12:53:25 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_env(char **envp, t_command *command)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[i])
		i++;
	command->my_env = (char **)malloc((i + 1) * sizeof(char *));
	while (j <= i)
	{
		command->my_env[j] = my_strdup(envp[j]);
		j++;
	}
	command->my_env[j] = '\0';
	return (command->my_env);
}

void	set_command(t_command *command)
{
	command->prompt = make_prompt();
	command->input = readline(command->prompt);
}
