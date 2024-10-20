
#include "../../includes/minishell.h"

/**
 * pre_exec - Prepares the command for execution by handling expansions.
 *
 * This function removes quotes from the command input and performs variable
 * expansion. It processes both simple and double quotes. If any redirection
 * setup fails, the function returns an error code.
 *
 * @param command: A pointer to the `t_command` structure that holds the command
 * input and associated data.
 */

int	pre_exec(t_command *command)
{
	single_quotes_to_unprintable(command->l_input);
	remove_all_quotes(command->l_input, SIMPLE_QUOT_MARK);
	var_exp(command);
	remove_all_quotes(command->l_input, DOUBLE_QUOT_MARK);
	remove_all_quotes(command->l_input, UNPRINT_CHAR);
	remove_empty_nodes(command->l_input);
	return (NO_ERROR);
}
