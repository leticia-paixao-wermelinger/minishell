/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:45:54 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/17 11:59:29 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern volatile unsigned int    g_status;

char    *remove_after_double_pipe(char **str, int i);

/*
The following function checks if the string starts or ends with a Pipe.
*/

int	check_pipe_init_and_end(char *str)
{
	int	i;

	i = 0;
	if (str[i] == PIPE)
	{
		g_status = MISUSE;
		print_error("bash: syntax error near unexpected token `|'\n");
		return (ERROR);
	}
	while (str[i])
		i++;
	if (str[i - 1] == PIPE)
	{
		g_status = MISUSE;
		print_error("bash: syntax error near unexpected token `|'\n");
		return (ERROR);
	}
	return (NO_ERROR);
}

int	check_double_pipe_together(char **str)
{
	int	i;
	int	j;
	int	f_pipe;

	i = 1;
	j = 0;
	f_pipe = OFF;
	if (!*str)
		return (ERROR);
	while ((*str)[i])
	{
		if ((*str)[i] == PIPE && f_pipe == OFF)
		{
			j = i;
			f_pipe = ON;
		}
		else if ((*str)[i] == PIPE && f_pipe == ON)
		{
			*str = remove_after_double_pipe(str, j);
			return (NO_ERROR);
		}
		else if ((*str)[i] != PIPE && f_pipe == ON)
			f_pipe = OFF;
		i++;
	}
	return (NO_ERROR);
}

char	*remove_after_double_pipe(char **str, int i)
{
	char	*temp;

	temp = my_strldup(*str, i);
	free(*str);
	*str = NULL;
	return (temp);
}
/*
int	check_following_pipes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (NO_ERROR);
}
*/
/*
The following function checks if there are pipes and redirects put together
*/
/*
static int	check_pipe_and_redir(char *str)
{
	int	i;
	int	fpipe;
	int	fredir;

	i = 0;
	fpipe = OFF;
	fredir = OFF;
	while (str[i])
	{
		if (str[i] == PIPE)
			fpipe = ON;
		else if (str[i] == LESS_THAN || str[i] == GREATER_THAN)
			fredir = ON;

		i++;
	}
	return (NO_ERROR);
}*/
