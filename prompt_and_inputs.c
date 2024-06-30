/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_and_inputs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:02:36 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/06/30 19:15:18 by lpaixao-         ###   ########.fr       */
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
//	else if (my_strcmp(command.input, __) == 0)
	else //Apenas para testar a função my_getenv e comparar com a getenv original
	{
		my_printf("Minha getenv: %s\n", my_getenv_by_list(command->input, command->my_env));
		my_printf("getenv original: %s\n", getenv(command->input));
	}
	return (0);
}
