/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:43:07 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/01 23:16:59 by lraggio          ###   ########.fr       */
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



// ---- MUDAR A DOCUMENTAÇÃO DESSA FUNÇÃO

void	signal_handle(int sig)
{
	if (sig == SIGINT)
	{
		if (RL_ISSTATE(RL_STATE_READCMD))
			ioctl(STDIN_FILENO, TIOCSTI, "\n");
		else
			write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		g_status(USED_CTRL_C);
	}
	return ;
}

void	signal_heredoc_handle(int sig)
{
	if (sig == SIGINT)
		g_status(USED_CTRL_C);
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
	signal(SIGINT, signal_handle);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_heredoc_signal_handling(void)
{
	struct sigaction	sa;

	my_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = signal_heredoc_handle;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
