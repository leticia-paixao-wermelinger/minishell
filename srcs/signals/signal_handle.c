/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:43:07 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/13 15:39:41 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern volatile unsigned int    g_flag;

/**
 * signal_handle - Handles the SIGINT signal (Ctrl + C) during command input.
 *
 * This function manages the behavior of the shell when receiving the SIGINT
 * signal, which occurs when the user presses Ctrl + C. It checks if the signal
 * is received while the shell is in a state of reading a command (`RL_STATE_READCMD`).
 * If the shell is reading input, it simulates the user pressing Enter (`ioctl`
 * with TIOCSTI) to interrupt the current input. If not, it simply writes a newline.
 *
 * After handling the signal, it resets the input line using `rl_replace_line` and
 * `rl_on_new_line`, prepares the shell for new input, and updates the global
 * flags (`g_status` and `g_flag`) to indicate that an interrupt occurred.
 *
 * @param sig: The signal number received by the process (expected SIGINT).
 *
 * @note Behavior:
 * - If the shell is reading input, it simulates an Enter press.
 * - If not, it writes a new line to the terminal.
 * - The shell does not exit; it continues to run and waits for further input.
 * - Updates global flags to indicate the interrupt.
 *
 * @return void: This function does not return a value.
 */

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
		g_flag = 130;
	}
	return ;
}

/**
 * setup_signal_handling - Configures signal handling for SIGINT and SIGQUIT in the shell.
 *
 * This function sets up the signal handlers for the shell. It uses `signal()` to
 * assign the `signal_handle` function as the handler for SIGINT (Ctrl + C), ensuring
 * that the shell can manage command line interruptions without terminating the process.
 * It also ignores SIGQUIT (Ctrl + \) by setting it to `SIG_IGN`, so pressing Ctrl + \
 * has no effect in the shell.
 *
 * @note This function ensures that:
 * - Ctrl + C interrupts command input without exiting the shell.
 * - Ctrl + \ (SIGQUIT) is ignored.
 *
 * @return void: This function does not return a value.
 */

void	setup_signal_handling(void)
{
	signal(SIGINT, signal_handle);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * heredoc_signal_handle - Handles SIGINT during heredoc input.
 *
 * This function handles the SIGINT signal (Ctrl + C) during heredoc input in the shell.
 * When SIGINT is received, the function temporarily ignores further SIGINT signals,
 * updates the global status to indicate that Ctrl + C was used, and exits the heredoc
 * input process with a status code of 130, signaling that the input was interrupted.
 *
 * For any other signals, it clears the current input line and prepares the shell
 * for new input by simulating a newline using `ioctl`.
 *
 * @param sig: The signal number received by the process (expected SIGINT).
 *
 * @note Behavior:
 * - If SIGINT is received, it interrupts heredoc input and exits with status 130.
 * - For any other signals, it clears the input line and simulates a newline.
 *
 * @return void: This function does not return a value.
 */

void	heredoc_signal_handle(int sig)
{
	if (sig == SIGINT)
	{
		signal(SIGINT, SIG_IGN); // Temporarily ignore SIGINT after handling
		g_status(USED_CTRL_C); //Update global status after receiving Ctrl+C
		exit(130); // Exit heredoc with status 130
	}
	else
	{
		ioctl(1, TIOCSTI, 1); // Simulate newline input
		rl_on_new_line(); // Prepare readline for a new line
		rl_replace_line("", 0); // Clear the current input line
	}
}

/**
 * setup_heredoc_signal_handling - Configures signal handling for heredoc operations.
 *
 * This function sets up signal handling specifically for heredoc input, which differs
 * from standard shell command input. It uses `sigaction` to define custom handlers
 * for SIGINT and SIGQUIT. For SIGINT (Ctrl + C), the `signal_heredoc_handle` function
 * is used to manage the signal, allowing the shell to terminate heredoc input and exit
 * with a specific status code. SIGQUIT (Ctrl + \) is ignored by setting its handler to
 * `SIG_IGN`.
 *
 * @note This is useful when the shell expects multi-line heredoc input, and signals need
 * to be handled differently to avoid shell termination.
 *
 * @return void: This function does not return a value.
 */

void	setup_heredoc_signal_handling(void)
{
	struct sigaction	sa;

	my_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = heredoc_signal_handle;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
