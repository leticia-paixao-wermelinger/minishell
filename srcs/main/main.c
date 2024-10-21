
#include "../../includes/minishell.h"

volatile unsigned int	g_flag;

/**
 * @brief ms_loop - The main loop of the minishell that processes user input.
 *
 * This function continuously prompts the user for input, processes the
 * input command, and executes it. The loop will terminate when the
 * input is NULL or an error occurs during command processing.
 *
 * @param command: A t_command structure that holds information about
 *                 the command to be executed, including input and
 *                 tokenized commands.
 *
 * @note The loop will:
 *       - Call `set_command` to set the input command.
 *       - Clear the input if it is NULL or empty, and skip the iteration.
 *       - Add the input command to the history if it is valid.
 *       - Parse the command using the `parser` function.
 *       - Pre-execute checks with `pre_exec`.
 *       - Execute the command through the `executor`.
 *       - Clear the command structure for the next iteration.
 *       - The loop runs indefinitely until it is explicitly broken.
 */

void	exec_and_clear(t_command command)
{
	executor(&command, command.l_input);
	clear_loop_end(&command);
}

void	ms_loop(t_command command)
{
	while (42)
	{
		set_command(&command);
		command.input_count++;
		if (command.input == NULL)
		{
			clear_input(&command);
			g_status(NO_ERROR);
			break ;
		}
		add_history(command.input);
		if (my_strlen(command.input) == 0)
		{
			clear_input(&command);
			continue ;
		}
		if (parser(&command) == ERROR)
			continue ;
		if (pre_exec(&command) == ERROR)
		{
			clear_loop_end(&command);
			break ;
		}
		exec_and_clear(command);
	}
}

/**
 * @brief main - The entry point of the minishell program.
 *
 * This function initializes the command structure, sets up the signal
 * handling, retrieves environment variables, and enters the main loop
 * of the minishell. It also checks for command-line arguments.
 *
 * @param argc: The count of command-line arguments.
 * @param argv: An array of command-line argument strings.
 *
 * @return int: Returns ERROR if there are command-line arguments other
 *              than the program name, otherwise returns the result of
 *              the `ms_loop` function.
 *
 * @note If there are command-line arguments, it prints an error message
 *       and returns ERROR. It initializes the command structure using
 *       `my_bzero` and calls `setup_signal_handling` to handle signals
 *       appropriately during command execution.
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
