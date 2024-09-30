/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:41:32 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/27 21:56:10 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void clear_all(t_command *command, int ret);

/*
Eu não estou entendendo. Nos meus testes:

$ exit 3 8
exit
bash: exit: too many arguments
echo $?
1

e em:

exit h
exit
bash: exit: h: numeric argument required
$ echo $?
2

Em ambos imprime o "exit", mas apenas no segundo caso que efetivamente sai do bash. No primeiro não sai....
*/

int	my_exit(t_tokens *token, t_command *command)
{
	int	ret;

	printf("exit\n");
	if (token == NULL) // Está sem parâmetro
		ret = g_status(-1);
	else
	{
		ret = my_atoi(token->word);
		if (ret == 0 && strcmp(token->word, "0") != 0) // Argumento não numérico
		{
			print_error("minishell: exit: ");
			print_error(token->word);
			print_error(": numeric argument required\n");
			ret = MISUSE;
		}
		else if (token->next != NULL) // Tem mais de um argumento
		{
			print_error("minishell: exit: too many arguments\n");
			return(ERROR);
		}
		else
			g_status(ret);
	}
	clear_all(command, ret);
	return (ERROR);
}

static void	clear_all(t_command *command, int ret)
{
	clear_loop_end(command);
	final_clear(command);
	exit(ret);
}
