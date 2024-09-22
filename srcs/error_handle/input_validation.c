/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:58:44 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/22 00:27:33 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	first_input_validation(t_command *command)
{
	if (!(command->input))
		return (ERROR);
	remove_closed_in_quotes_metas(command->input);
	if (n_quote_validation(command->input) == ERROR)
		return (ERROR);
	else if (check_pipe_init_and_end(command->input) == ERROR)
		return (ERROR);
	else if (check_following_pipes(command->input) == ERROR)
		return (ERROR);
	else if (check_pipes_with_redir(command->input) == ERROR)
		return (ERROR);
	else if (input_ends_with_redir(command->input) == ERROR)
		return (ERROR);
	return_closed_in_quotes_metas(command->input);
	return (NO_ERROR);
}

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
			if (token->word == NULL || token->word[0] == DOUBLE_QUOT_MARK || token->word[0] == SIMPLE_QUOT_MARK)
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
