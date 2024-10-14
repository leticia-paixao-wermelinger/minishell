/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_redir_validation.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 20:21:02 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/21 20:37:09 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//static int  pipe_first(char *str, int i);
static int	redir_first(char *str, int i);

int	check_pipes_with_redir(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		/*if (str[i] == PIPE)
		{
			if (pipe_first(str, i) == ERROR)
				return (ERROR);
		}*/
		if (str[i] == LESS_THAN || str[i] == GREATER_THAN)
		{
			if (redir_first(str, i) == ERROR)
				return (ERROR);
		}
		i++;
	}
	return (NO_ERROR);
}

/*
Verify cases such as echo | < ls or echo | < ls | wc. In both cases, the result must be:
bash:  ls: No such file or directory
However, the g_status must be 0.
*/

/*static int	pipe_first(char *str, int i)
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

/*
Verify if there are any errors with redir followed by other redirs or with redir followed by pipe.
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
		else if (str[i] != PIPE && str[i] != LESS_THAN && str[i] != GREATER_THAN && str[i] != SPACE_CHAR)
			return (NO_ERROR);
		i++;
	}
	return (NO_ERROR);
}
