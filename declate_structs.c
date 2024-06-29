/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declate_structs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:32:50 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/06/28 23:18:46 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static void	print_matrix(char **matrix)
{
	int	i = 0;

	while (matrix[i])
	{
		my_printf("%s\n", matrix[i]);
		i++;
	}
}
*/
void    copy_env(t_command *command)
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


void	set_command(t_command *command)
{
	command->prompt = make_prompt();
	command->input = readline(command->prompt);
}
