/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:43:07 by lraggio           #+#    #+#             */
/*   Updated: 2024/09/18 17:18:19 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * signal_handle - Handles signals SIGINT (Ctrl + C) and SIGQUIT (Ctrl + \).
 * 
 * This function handles the behavior of the shell when receiving the SIGINT 
 * and SIGQUIT signals. For SIGINT (Ctrl + C), it prints a new prompt without 
 * exiting the shell. For SIGQUIT (Ctrl + \), it ignores the signal and does nothing.
 *
 * @param sig: The signal number received by the process.
 */

void	signal_handle(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_status(USED_CTRL_C);
	}
	else if (sig == SIGQUIT)
		return ;
}

/**
 * setup_signal_handling - Configures signal handlers for SIGINT and SIGQUIT.
 * 
 * This function sets up the signal handlers for SIGINT (Ctrl + C) and SIGQUIT 
 * (Ctrl + \) using `sigaction`. It assigns `signal_handle` as the handler for 
 * SIGINT to manage interrupts in the shell and ignores SIGQUIT.
 *
 * If the signal handler setup fails for any of the signals, it calls `handle_sig_error`.
 */

void	setup_signal_handling(void)
{
	struct sigaction	sa;

	my_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = signal_handle;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		handle_sig_error(SIGINT);
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		handle_sig_error(SIGQUIT);
}

/**
 * handle_sig_error - Handles errors during signal setup.
 * 
 * This function is called when an error occurs during the setup of signal handlers 
 * for SIGINT or SIGQUIT. It prints an error message and terminates the program 
 * with a failure status if the setup for either signal fails.
 *
 * @param sig: The signal number that failed during handler setup.
 */

void	handle_sig_error(int sig)
{
	if (sig == SIGINT)
	{
		perror(("Error setting up SIGINT handler\n"));
		exit(EXIT_FAILURE);
	}
	else if (sig == SIGQUIT)
	{
		perror(("Error setting up SIGQUIT handler\n"));
		exit(EXIT_FAILURE);
	}
	else
		return ;
}