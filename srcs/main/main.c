/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 00:41:47 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/15 17:06:36 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

volatile unsigned int    g_status;

int	main(int argc, char *argv[])
{
	t_command	command;

	my_bzero(&command, sizeof(t_command));
	if (argc > 1)
	{
		my_printf("bash: %s: No such file or directory\n", argv[1]);
		return 0;
	}
	setup_signal_handling();
	get_env(&command);
	while (42)
	{
		set_command(&command);
		if (command.input == NULL)
		{
			clear_input(&command);
			break ;
		}
		else if (my_strlen(command.input) == 0)
		{
			clear_input(&command);
			continue ;
		}
		add_history(command.input);
		if (first_input_validation(&command) == ERROR)
		{
			clear_input(&command);
			continue ;
		}
		parser(&command);
//		lexer(&command);
//		printf("Printar lista do input:\n");
//		printlist(command.l_input);
		remove_all_quotes(command.l_input, DOUBLE_QUOT_MARK);
		var_exp(&command);
		remove_all_quotes(command.l_input, SIMPLE_QUOT_MARK);
		if (run_commands(&command) == CLOSE)
		{
			clear_loop_end(&command);
			break ;
		}
		clear_loop_end(&command);
	}
	final_clear(&command);
}
