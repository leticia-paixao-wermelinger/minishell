/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_and_inputs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:02:36 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/06 17:23:55 by lpaixao-         ###   ########.fr       */
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
	t_node		*list;
	t_tokens	*temp_words;
	int		ret;

	ret = NO_INFO;
	list = command->l_input;
	while (list)
	{
		temp_words = list->token;
		while (temp_words)
		{
			if (is_builtin(temp_words) == TRUE)
				ret = run_builtin(command, list, 1); // a função está enviando fd 1 por padrão. deverá ser ajustado isso posteriormente para enviar um fd específico
			else
				printf("Não é builtin. Ainda estou criando as builtins\n");
			if (ret == ERROR)
			{
//				printf("Validar erro\n");
				return (ERROR);
			}
			else if (ret == CLOSE)
				return (CLOSE);
		}
		list = list->next;
	}
	return (ret);
}
