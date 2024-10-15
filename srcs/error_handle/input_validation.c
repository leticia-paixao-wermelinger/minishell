/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:58:44 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/10/14 18:44:56 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * first_input_validation - Validates the initial command input.
 *
 * This function checks the validity of the command input by performing several
 * validation steps. It ensures that the input is not null, does not contain only
 * spaces, and that it is well-formed with respect to quotes, pipes, and
 * redirections. If any validation fails, an error is returned. The function
 * also removes unnecessary spaces and fixes any issues with closed quotes.
 *
 * @param command: A pointer to the command structure containing the input
 *                 to be validated.
 *
 * @return int: Returns `NO_ERROR` if the input is valid; otherwise,
 *              returns `ERROR`.
 */

int	first_input_validation(t_command *command)
{
	if (!(command->input))
		return (ERROR);
	else if (only_spaces(command->input) == ERROR)
		return (ERROR);
	remove_closed_in_quotes_metas(command->input);
	command->input = remove_init_and_end_spaces(command->input);
	if (check_pipe_init_and_end(command->input) == ERROR)
		return (ERROR);
	else if (n_quote_validation(command->input) == ERROR)
		return (ERROR);
	else if (check_following_pipes(command->input) == ERROR)
		return (ERROR);
	else if (check_pipes_with_redir(command->input) == ERROR)
		return (ERROR);
	else if (input_ends_with_redir(command->input) == ERROR)
		return (ERROR);
	command->input = fix_lack_of_spaces(command->input);
	return_closed_in_quotes_metas(command->input);
	return (NO_ERROR);
}

/**
 * general_input_validation - Validates the tokens in a command node.
 *
 * This function iterates through the linked list of command nodes and their
 * associated tokens, checking each token for validity. It verifies that tokens
 * are not null and do not begin with quote marks. The function also checks
 * that redirection operators are correctly placed in relation to the tokens.
 * If any validation fails for a token, an error is returned.
 *
 * @param node: A pointer to the command node containing the tokens to be
 *              validated.
 *
 * @return int: Returns `NO_ERROR` if all tokens are valid; otherwise,
 *              returns `ERROR`.
 */

int	general_input_validation(t_node *node)
{
	t_node		*temp;
	t_tokens	*token;

	temp = node;
	while (temp)
	{
		token = temp->token;
		while (token)
		{
			if (token->word == NULL || token->word[0] == DOUBLE_QUOT_MARK
				||token->word[0] == SIMPLE_QUOT_MARK)
			{
				token = token->next;
				continue ;
			}
			if (check_following_redirs(token) == ERROR)
				return (ERROR);
			token = token->next;
		}
		temp = temp->next;
	}
	return (NO_ERROR);
}
