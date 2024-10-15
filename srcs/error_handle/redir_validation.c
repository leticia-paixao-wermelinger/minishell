/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 20:37:50 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/10/14 22:39:56 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * input_ends_with_redir - Checks if the input ends with a redirection symbol.
 *
 * This function scans the input string `str` from the end to check if the
 * last non-space character is a redirection symbol ('<' or '>'). If a
 * redirection symbol is found at the end, it prints a syntax error message
 * and sets the global status to MISUSE.
 *
 * @param str: The input string to check.
 *
 * @return ERROR if the input ends with a redirection symbol.
 *         NO_ERROR if the input does not end with a redirection symbol.
 */

int	input_ends_with_redir(char *str)
{
	int	i;

	i = my_strlen(str);
	while (--i >= 0)
	{
		if (str[i] != SPACE_CHAR && str[i] != LESS_THAN
			&& str[i] != GREATER_THAN)
			return (NO_ERROR);
		else if (str[i] == LESS_THAN || str[i] == GREATER_THAN)
			break ;
	}
	print_error("minishell: syntax error near unexpected token `newline'\n");
	g_status(MISUSE);
	return (ERROR);
}

/**
 * check_following_redirs - Validates consecutive redirections in a token list.
 *
 * This function checks two consecutive tokens in the list `node` and `next`.
 * If both tokens are redirection symbols, it triggers a syntax error, printing
 * an appropriate message and returning ERROR.
 *
 * @param node: The current token node to check.
 *
 * @return ERROR if two consecutive redirection tokens are found.
 *         NO_ERROR if no such error is detected.
 */

int	check_following_redirs(t_tokens *node)
{
	t_tokens	*next;

	next = node->next;
	if (token_is_redir(node) == TRUE && token_is_redir(next) == TRUE)
		return (redir_syntax_error(next->type));
	return (NO_ERROR);
}
