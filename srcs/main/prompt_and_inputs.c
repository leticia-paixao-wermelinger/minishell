/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_and_inputs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:02:36 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/18 17:18:19 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * set_command - Prepares the command structure for each new input.
 * 
 * This function generates the shell prompt using the current working directory, 
 * then reads user input via `readline` and stores it in the `command->input` field. 
 * It also frees the previous prompt string if necessary.
 *
 * @param command: A pointer to the `t_command` structure that holds the command 
 * input and related data.
 */

void	set_command(t_command *command)
{
	command->prompt = make_prompt();
	command->input = readline(command->prompt);
}

/**
 * make_prompt - Generates a shell prompt string.
 * 
 * This function creates a prompt string that consists of the current working directory 
 * followed by a dollar sign. It uses ANSI escape codes to color the directory path in green. 
 * The result is dynamically allocated and should be freed after use.
 *
 * @return char*: The generated prompt string.
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
