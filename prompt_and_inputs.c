/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_and_inputs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:02:36 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/07/01 16:40:45 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_prompt(void)
{
	char	cwd[1824];
	char	*prompt;
	char	*temp;

	getcwd(cwd, sizeof(cwd));
	temp = my_strjoin("\033[0;32m", cwd);
	prompt = my_strjoin(temp, "\033[0m$ ");
	free(temp);
	return (prompt);
}

int	check_inputs(t_command *command)
{
	if (my_strcmp(command->input, "env") == 0)
		print_env(command->my_env);
	// O else if abaixo serve apenas para teste, pois precisaremos ainda passar a split e fazer essa verificação de outra forma:
/*	else if (my_strcmp(command.input, "export") == 0)
		export(name, command);*/
//	else if (my_strcmp(command.input, __) == 0)
//	else if (my_strcmp(command.input, __) == 0)
	return (0);
}
