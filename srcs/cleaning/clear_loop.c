
#include "../../includes/minishell.h"

/**
 * clear_loop_end - Frees resources associated with the command loop.
 *
 * This function is called to free the resources related to the current command
 * loop. It invokes `free_list()` to free the linked list of input tokens and
 * `clear_input()` to free the command prompt and input.
 *
 * @param command: The command structure containing resources to be freed.
 *
 * @return void: This function does not return a value.
 */

void	clear_loop_end(t_command *command)
{
	free_list(command->l_input);
	clear_input(command);
}

/**
 * clear_input - Frees input-related resources in the command structure.
 *
 * This function frees the memory allocated for the command prompt and input
 * string. If the input matrix is not NULL, it calls `my_clean_vect()` to free
 * the matrix.
 *
 * @param command: The command structure containing input resources to be freed.
 *
 * @return void: This function does not return a value.
 */

void	clear_input(t_command *command)
{
	free(command->prompt);
	free(command->input);
	if (command->input_matrix != NULL)
		my_clean_vect(command->input_matrix);
}

/**
 * final_clear - Performs final cleanup before shell termination.
 *
 * This function is called to perform final cleanup operations. It clears the
 * history, frees the environment variables, and may need to be updated to use
 * `rl_clear_history()` for proper history management.
 *
 * @param command: The command structure containing resources to be freed.
 *
 * @return void: This function does not return a value.
 */

void	final_clear(t_command *command)
{
	rl_clear_history();
	free_env(command->my_env);
}
