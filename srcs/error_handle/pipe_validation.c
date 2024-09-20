/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:45:54 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/20 17:03:23 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_following_pipes_in_loop(char *str, int i, int count_first_pipes, int count_sec_pipes);
static int	check_error_pipes(int first_pipes, int sec_pipes);

extern volatile unsigned int    g_status;

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

int	check_following_pipes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		return (check_following_pipes_in_loop(str, i, 0, 0));
		i++;
	}
	return (NO_ERROR);
}

static int	check_following_pipes_in_loop(char *str, int i, int count_first_pipes, int count_sec_pipes)
{
	int	f_pipe;
	int	space_between_pipes;

	f_pipe = OFF;
	space_between_pipes = 0;
	printf("Está na check_following_pipes_in_loop, com str[%i] = %c\n", i, str[i]);
	if (str[i] == PIPE && f_pipe == OFF)
	{
		count_first_pipes += 1;
		f_pipe = ON;
	}
	else if (str[i] == SPACE_CHAR)
		space_between_pipes = 1;
	else if (str[i] == PIPE && f_pipe == ON && space_between_pipes == 0)
		count_first_pipes += 1;
	else if (str[i] == PIPE && f_pipe == ON && space_between_pipes != 0)
		count_sec_pipes += 1;
	else if (str[i] != PIPE && str[i] != SPACE_CHAR && f_pipe == ON)
	{
		printf("Vai chamar a check_error_pipes com count_first_pipes = %i & com count_sec_pipes = %i\n", count_first_pipes, count_sec_pipes);
		if (check_error_pipes(count_first_pipes, count_sec_pipes) == ERROR)
			return (ERROR);
		f_pipe = OFF;
		count_first_pipes = 0;
		count_sec_pipes = 0;
		space_between_pipes = 0;
	}
	return (NO_ERROR);
}

static int	check_error_pipes(int first_pipes, int sec_pipes)
{
	if ((first_pipes == 1 || first_pipes == 2) && sec_pipes == 1)
		return (print_pipe_syntax_error(1));
	else if (first_pipes == 1 && sec_pipes >= 2)
		return (print_pipe_syntax_error(2));
	else if (first_pipes == 3)
		return (print_pipe_syntax_error(1));
	return (NO_ERROR);
}

/*
The following function checks if there are two pipestogether (without spaces between them)
and removes them and what comes after them.
*/
/*
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
}*/
