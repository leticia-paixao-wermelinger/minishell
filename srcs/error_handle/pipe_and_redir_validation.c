/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_redir_validation.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 20:21:02 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/10/14 18:57:40 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	redir_first(char *str, int i);

/**
 * check_pipes_with_redir - Checks for syntax errors between pipes and redir.
 *
 * This function iterates through the input string and verifies if there are
 * any syntax errors involving pipes and redirection operators. It checks
 * if a redirection operator is immediately followed by a pipe or if there
 * are multiple consecutive redirections.
 *
 * @param str: The input string containing the command line to be checked.
 *
 * @return int: Returns NO_ERROR if there are no syntax errors, or ERROR
 *              if any issues are found.
 */

int	check_pipes_with_redir(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == LESS_THAN || str[i] == GREATER_THAN)
		{
			if (redir_first(str, i) == ERROR)
				return (ERROR);
		}
		i++;
	}
	return (NO_ERROR);
}

/**
 * pipe_first - Checks for syntax errors related to pipes.
 *
 * This function verifies if a pipe is followed by a valid input and checks
 * for errors in the context of redirection operators. If a less-than symbol
 * appears after a pipe, an error message is printed, and the status is updated.
 *
 * @param str: The input string containing the command line to be checked.
 * @param i: The current index in the input string where a pipe was found.
 *
 * @return int: Returns NO_ERROR if no issues are found, or ERROR if any
 *              errors are detected, such as a less-than symbol without a
 *              valid input.
 *

static int	pipe_first(char *str, int i)
{
	char	*s_err;

	i++;
	s_err = NULL;
	while (str[i])
	{
		if (str[i] == LESS_THAN && str[i + 1] != LESS_THAN)
		{
			s_err = fromstrldup(str, i + 1);
			if (is_there_space(s_err) == TRUE)
				s_err = strdup_tillc(s_err);
			print_error("minishell: ");
			print_error(s_err);
			print_error(": No such file or directory\n");
			g_status(NO_ERROR);
			free(s_err);
			return (ERROR);
		}
		else if (str[i] != SPACE_CHAR)
			break ;
		i++;
	}
	return (NO_ERROR);
}*/

/**
 * redir_first - Checks for errors related to redirection operators.
 *
 * This function verifies the position of redirection operators in the input
 * string, checking for errors such as consecutive redirections or a redirection
 * followed by a pipe. If an error is found, it calls the appropriate error
 * handling function.
 *
 * @param str: The input string containing the command line to be checked.
 * @param i: The current index in the input string where a redirection was found.
 *
 * @return int: Returns NO_ERROR if no issues are found, or ERROR if any
 *              errors are detected.
 */

static int	redir_first(char *str, int i)
{
	i++;
	if (str[i] == LESS_THAN || str[i] == GREATER_THAN)
		i++;
	while (str[i])
	{
		if (str[i] == PIPE)
		{
			if (str[i + 1] == PIPE)
				pipe_syntax_error(2);
			else
				pipe_syntax_error(1);
			return (ERROR);
		}
		else if (str[i] != PIPE && str[i] != LESS_THAN
			&& str[i] != GREATER_THAN && str[i] != SPACE_CHAR)
			return (NO_ERROR);
		i++;
	}
	return (NO_ERROR);
}
