
#include "../../includes/minishell.h"

extern volatile unsigned int	g_flag;

/**
 * signal_handle - Handles the SIGINT signal (Ctrl + C) during command input.
 *
 * This function manages the behavior of the shell when receiving the SIGINT
 * signal, which occurs when the user presses Ctrl + C. It checks if the sig
 * is received while the shell is in a state of reading a command
 * (`RL_STATE_READCMD`).
 * If the shell is reading input, it simulates the user pressing Enter
 * (`ioctl`with TIOCSTI) to interrupt the current input. If not, it simply
 * writes a newline.
 *
 * After handling the signal, it resets the input line using
 * `rl_replace_line` and `rl_on_new_line`, prepares the shell for new input,
 *  and updates the global flags (`g_status` and `g_flag`) to indicate that
 * an interrupt occurred.
 *
 * @param sig: The signal number received by the process (expected SIGINT).
 *
 * @note Behavior:
 * - If the shell is reading input, it simulates an Enter press.
 * - If not, it writes a new line to the terminal.
 * - The shell does not exit; it continues to run and waits for further
 * input.
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
 * @brief Set up signal handlers for heredoc input.
 *
 * This function configures the shell to handle signals appropriately
 * during heredoc input. It sets the handler for SIGINT to
 * `heredoc_signal_handle` and ignores the SIGQUIT signal.
 */

void	setup_signal_handling(void)
{
	signal(SIGINT, signal_handle);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @brief heredoc_signal_handle - Handles signals related to heredoc processing.
 *
 * This function is called when a signal, such as SIGINT (Ctrl+C), is received
 * during the reading of a heredoc. Depending on the received signal,
	the function
 * may ignore it or replace the current line in the reading interface.
 *
 * @param sig The received signal, which may be SIGINT or another signal.
 *
 * When SIGINT is received,
	the function sets the signal handler to ignore further

* SIGINT signals to prevent additional interruptions. It also updates the
* global status to indicate that Ctrl+C was used and exits with status
*code 130.
 *
 * When a different signal is received, the function uses ioctl to inject
 * a newline char into the terminal input stream. This simulates the effect
 * of the user pressing Enter, allowing the terminal to process the current
 * line appropriately.
 */

/**
 * @brief ioctl - Injects a character into the terminal input stream.
 *

* The ioctl function is used here with the TIOCSTI request code to simulate
* user input directly into the terminal. It allows the shell to process the
* heredoc input correctly, even when interrupted by signals.
 *
 * @param fd The file descriptor for the terminal (1 for STDOUT_FILENO).

* @param request The request code (TIOCSTI) that indicates to inject a char.
 * @param data The character to be injected (in this case, a newline).
 *

* This function allows for seamless continuation of the input process by ensuring
 * that the terminal recognizes a new line, which can help maintain the flow of
 * the heredoc reading process even in the event of an interrupt.
 */

/**
 * @brief setup_heredoc_signal_handling
- Initializes signal handling for heredoc
 * processing.
 *

* This function sets up the signal handlers specifically for heredoc operations.
 * It configures the SIGINT handler to use the heredoc_signal_handle function
 * and ignores the SIGQUIT signal.
 *
 */

void	heredoc_signal_handle(int sig)
{
	if (sig == SIGINT)
	{
		signal(SIGINT, SIG_IGN);
		g_status(USED_CTRL_C);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
	}
	else
	{
		ioctl(1, TIOCSTI, 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

/**
 * @brief Sets up signal handling for heredoc input.
 *
 * This function installs a signal handler for SIGINT (Ctrl+C) during
 * heredoc reading. It ensures that when the signal is received, the
 * handler will execute the `heredoc_signal_handle` function to manage
 * the signal appropriately. Additionally, it ignores the SIGQUIT signal.
 *
 * This setup is essential for providing a responsive user experience
 * when entering heredoc input, allowing the user to cancel the input
 * gracefully.
 *
 * sigemptyset - Initialize the signal mask to empty.
 * sigaction -- Install the signal handler for SIGINT or SIGQUIT.
 * sa.sa_handler = SIG_IGN -- Ignore the SIGQUIT signal.
 * sigaction(SIGQUIT, &sa, NULL) -- Install the ignore action for SIGQUIT.
 * @param None
 * @return None
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
