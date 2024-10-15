/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_and_inputs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:02:36 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/10/15 19:01:01 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief set_command - Sets the current command input for the minishell.
 *
 * This function generates a prompt string using the `make_prompt`
 * function, displays it to the user, and reads the user's input
 * using the `readline` function. The input is stored in the
 * `input` field of the provided `t_command` structure.
 *
 * @param command: A pointer to a t_command structure that holds
 *                 the current command state, including the prompt
 *                 and user input.
 *
 * @note The function dynamically allocates memory for the prompt.
 *       It is the caller's responsibility to free this memory
 *       when it is no longer needed.
 */

void	set_command(t_command *command)
{
	command->prompt = make_prompt();
	command->input = readline(command->prompt);
}

/**
 * @brief make_prompt - Generates a shell prompt string with the current working
 * directory.
 *
 * This function retrieves the current working directory using the
 * `getcwd` function and constructs a formatted prompt string.
 * The prompt is prefixed with a green color escape code and
 * suffixed with a reset color escape code, followed by a dollar sign
 * ("$ ") to indicate readiness for user input.
 *
 * @return A pointer to a dynamically allocated string containing
 *         the formatted prompt. The caller is responsible for
 *         freeing this memory when it is no longer needed.
 *
 * @note If `getcwd` fails, the returned prompt may be incorrect
 *       or incomplete, but the function does not handle this error.
 */

char	*make_prompt(void)
{
	char	cwd[1824];
	char	*prompt;
	char	*temp;

	getcwd(cwd, sizeof(cwd));
	temp = my_strjoin("\033[0;32m", cwd);
	prompt = my_strjoin(temp, "\033[0m$ ");
	free(temp);
	return (prompt);
}
