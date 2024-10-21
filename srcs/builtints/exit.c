
#include "../../includes/minishell.h"

static void	clear_all(t_command *command);

/**
 * my_exit - Handles the 'exit' built-in command.
 *
 * This function implements the behavior of the 'exit' command in the 
 * minishell. It displays "exit" and then checks the provided tokens to 
 * determine the exit status. If no token is passed, it uses the global 
 * status value (`g_status`). If a token is passed, the function attempts 
 * to convert it to an integer and uses it as the exit code. If the token 
 * is non-numeric, an error message is printed, and a misuse code is 
 * returned. If more than one argument is provided, an error is shown, 
 * but the shell does not exit.
 *
 * The function calls `clear_all()` to free all resources before 
 * terminating the shell.
 *
 * @param token: A linked list of tokens, where the first token represents 
 *               the argument for the 'exit' command.
 * @param command: The command structure, used to free resources before 
 *                 exit.
 *
 * @note Behavior:
 * - If no argument is provided, the shell exits with the global status 
 *   value.
 * - If a non-numeric argument is provided, it prints an error and exits 
 *   with status 2.
 * - If more than one argument is provided, an error is printed, but the 
 *   shell does not exit.
 *
 * @return int: Returns `ERROR` if there are too many arguments; otherwise, 
 *              the function does not return, as the shell exits.
 */

int	my_exit(t_tokens *token, t_command *command)
{
	int	ret;

	printf("exit\n");
	if (token == NULL)
		ret = g_status(-1);
	else
	{
		ret = my_atoi(token->word);
		if (ret == 0 && strcmp(token->word, "0") != 0)
		{
			print_error("minishell: exit: ");
			print_error(token->word);
			print_error(": numeric argument required\n");
			ret = MISUSE;
		}
		else if (token->next != NULL)
		{
			print_error("minishell: exit: too many arguments\n");
			return (ERROR);
		}
		else
			g_status(ret);
	}
	clear_all(command);
	return (ERROR);
}

/**
 * clear_all - Frees resources and exits the shell with the appropriate 
 *             status.
 *
 * This function is called when the shell is about to terminate, usually by 
 * the 'exit' command. It first calls `clear_loop_end()` to free resources 
 * associated with the current command loop, and then `final_clear()` to 
 * release any remaining resources. After freeing all resources, the function 
 * exits the shell using the current value of `g_status`.
 *
 * @param command: The command structure containing resources to be freed.
 *
 * @return void: This function does not return a value, as it calls `exit()` 
 * to terminate the shell.
 */

static void	clear_all(t_command *command)
{
	clear_loop_end(command);
	final_clear(command);
	exit(g_status(-1));
}
