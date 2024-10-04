/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 00:41:47 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/10/03 23:44:22 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * ms_loop - The main loop of the minishell.
 *
 * This function runs the main loop of the shell, continuously prompting for user input,
 * parsing it, and executing commands until the user exits. It handles errors,
 * input clearing, and command execution. The loop terminates when the user inputs
 * an empty line, presses `Ctrl+D`, or when a critical error occurs.
 *
 * @param command: A structure of type `t_command` that holds the command input,
 * environment variables, and other necessary data for shell execution.
 */

void	ms_loop(t_command command)
{
	while (42)
	{
		set_command(&command);
		command.input_count++;
		if (command.input == NULL)
		{
			clear_input(&command);
			g_status(NO_ERROR); // Verificar se ta funcionando depois com execve, c ./minishell e vendo o retorno com echo $? depois de dar ctrl + d
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
		if (pre_exec(&command) == ERROR)
		{
			clear_loop_end(&command);
			break ;
		}
		executor(&command, command.l_input);
		clear_loop_end(&command);
	}
}

/**
 * main - The entry point of the minishell program.
 *
 * The `main` function initializes the `t_command` structure, checks for
 * command-line arguments (minishell does not accept any), sets up signal handling,
 * and begins the main shell loop (`ms_loop`). It also ensures that environment variables
 * are loaded and properly clears resources before exiting.
 *
 * @param argc: The argument count (should be 1 for minishell to run correctly).
 * @param argv: The argument vector (array of command-line arguments).
 *
 * @return int: Returns an error code if more than one argument is passed or upon critical failure.
 */

int	main(int argc, char *argv[])
{
	t_command	command;

	my_bzero(&command, sizeof(t_command));
	if (argc > 1)
		return (print_no_such_file(argv), ERROR);
	setup_signal_handling();
	get_env(&command);
	ms_loop(command);
	final_clear(&command);
}
