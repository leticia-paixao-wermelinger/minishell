/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:58:44 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/16 19:18:41 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	first_input_validation(t_command *command)
{
	if (n_quote_validation(command->input) == ERROR)
		return (ERROR);
	else if (check_pipe_init_and_end(command->input) == ERROR)
		return (ERROR);
//	else if (check_double_pipe......) // Remover o q vier depois na string
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
			if (token->word[0] == DOUBLE_QUOT_MARK || token->word[0] == SIMPLE_QUOT_MARK)
			{
				token = token->next;
				continue ;
			}
			/*if (validate_words(token->word) == ERROR)
				return (ERROR);*/
			token = token->next;
		}
		temp = temp->next;
	}
	return (NO_ERROR);
}
/*
int	validate_words(char *str)
{
	void(str);
	if (check_double_pipe(str) == ERROR)
		return (ERROR);
	return (NO_ERROR);
}*/
