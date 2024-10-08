/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:45:54 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/21 20:31:19 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_following_pipes_in_loop(char *str, int i, int ret);
static int	check_error_pipes(int first_pipes, int sec_pipes);

/*
The following function checks if the string starts or ends with a Pipe.
*/

int	check_pipe_init_and_end(char *str)
{
	int	i;

	i = 0;
	if (str[i] == PIPE)
	{
		pipe_syntax_error(1);
		return (ERROR);
	}
	while (str[i])
		i++;
	if (str[i - 1] == PIPE)
	{
		pipe_syntax_error(1);
		return (ERROR);
	}
	return (NO_ERROR);
}

int	check_following_pipes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (check_following_pipes_in_loop(str, i, NO_ERROR) == ERROR)
			return (ERROR);
		i++;
	}
	return (NO_ERROR);
}

static int	check_following_pipes_in_loop(char *str, int i, int ret)
{
	static int	f_pipe = OFF;
	static int	space_between_pipes = 0;
	static int	count_first_pipes = 0;
	static int	count_sec_pipes = 0;

	if (str[i] == PIPE && f_pipe == OFF)
	{
		count_first_pipes += 1;
		f_pipe = ON;
	}
	else if (str[i] == SPACE_CHAR && f_pipe == ON)
		space_between_pipes = 1;
	else if (str[i] == PIPE && f_pipe == ON && space_between_pipes == 0)
		count_first_pipes += 1;
	else if (str[i] == PIPE && f_pipe == ON && space_between_pipes != 0)
		count_sec_pipes += 1;
	else if (str[i] != PIPE && str[i] != SPACE_CHAR && f_pipe == ON)
	{
		ret = check_error_pipes(count_first_pipes, count_sec_pipes);
		f_pipe = OFF;
		count_first_pipes = 0;
		count_sec_pipes = 0;
		space_between_pipes = 0;
	}
	return (ret);
}

static int	check_error_pipes(int first_pipes, int sec_pipes)
{
	if ((first_pipes == 1 || first_pipes == 2) && sec_pipes == 1)
		return (pipe_syntax_error(1));
	else if (first_pipes == 1 && sec_pipes >= 2)
		return (pipe_syntax_error(2));
	else if (first_pipes == 3)
		return (pipe_syntax_error(1));
	return (NO_ERROR);
}