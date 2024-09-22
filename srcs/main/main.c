/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 00:41:47 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/21 22:54:32 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

volatile unsigned int    g_status;

void	ms_loop(t_command command)
{
	while (42)
	{
		printf("g_status = %i\n", g_status);
		set_command(&command);
		if (command.input == NULL)
		{
			clear_input(&command);
			g_status = NO_ERROR; // Verificar se ta funcionando depois com execve, c ./minishell e vendo o retorno com echo $? depois de dar ctrl + d
			break ;
		}
		else if (my_strlen(command.input) == 0)
		{
			clear_input(&command);
			continue ;
		}
		add_history(command.input);
		if (parser(&command) == ERROR)
			continue ;
//		printf("Printar lista do input:\n");
//		printlist(command.l_input);
		pre_exec(&command);
		if (executor(&command, command.l_input) == CLOSE)
		{
			clear_loop_end(&command);
			break ;
		}
		clear_loop_end(&command);
	}
}

int	main(int argc, char *argv[])
{
	t_command	command;

	my_bzero(&command, sizeof(t_command));
	if (argc > 1)
	{
		my_printf("bash: %s: No such file or directory\n", argv[1]); // Colocar no FD = 2
		return 0;
	}
	setup_signal_handling();
	get_env(&command);
	ms_loop(command);
	final_clear(&command);
}
