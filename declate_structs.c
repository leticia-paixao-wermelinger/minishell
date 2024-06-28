/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declate_structs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:32:50 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/06/27 21:43:10 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
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
}*/

void    copy_env(t_command *command)
{
	extern char	**environ;
	t_node		*temp;
	int			i;
	int			j;

	i = 0;
	j = 0;
	command->my_env = NULL;
	while (envp[i])
		i++;
	create_first_node(environ[j], command->my_env);
	temp = command->my_env->next;
	while (++j <= i)
	{
		create_last_node(environ[j], temp);
		temp = temp->next;
	}
//	return;
}


void	set_command(t_command *command)
{
	command->prompt = make_prompt();
	command->input = readline(command->prompt);
}
