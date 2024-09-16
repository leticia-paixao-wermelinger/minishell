/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:45:54 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/16 19:18:35 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
/*	{
		if (str[i] == PIPE && str[i + 1] == PIPE)
		{
			g_status = MISUSE;
			print_error("bash: syntax error near unexpected token `||'\n"); // fui testar e, em teoria, ele não dá erro aqui...
			return (ERROR);
		}*/
		i++;
//	}
	if (str[i - 1] == PIPE)
	{
		g_status = MISUSE;
		print_error("bash: syntax error near unexpected token `|'\n");
		return (ERROR);
	}
	return (NO_ERROR);
}
/* // Ta errado, c a split os 2 pipes não vão chegar nesse ponto
int	check_double_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == )
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
