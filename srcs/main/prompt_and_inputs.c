/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_and_inputs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:02:36 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/07/30 14:40:43 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	set_command(t_command *command)
{
	command->prompt = make_prompt();
	command->input = readline(command->prompt);
}

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

int	run_commands(t_command *command)
{
	t_node	*list;
	int		ret;

	ret = NO_INFO;
	list = command->l_input;
	while (list)
	{
		if (is_builtin(list->value) == TRUE)
			ret = run_builtin(command, list);
		else
			printf("Não é builtin. Ainda estou criando as builtins\n");
		if (ret == ERROR)
		{
//			printf("Validar erro\n");
			return (ERROR);
		}
		else if (ret == CLOSE)
			return (CLOSE);
		list = list->next;
	}
	return (ret);
}
