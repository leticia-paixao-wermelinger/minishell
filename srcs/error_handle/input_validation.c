/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:58:44 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/10 19:34:05 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int  check_pipe(char *str);
//static int	check_pipe_and_redir(char *str);

int	first_input_validation(t_command *command)
{
	if (check_pipe(command->input) == ERROR)
		return (ERROR);
/*	else if (check_pipe_and_redir(command->input) == ERROR)
		return (ERROR);*/
	return (NO_ERROR);
}

/*
The following function checks if the string starts or ends with a Pipe, or if
there are two consecutive Pipes, such as ||.
*/

static int	check_pipe(char *str)
{
	int	i;

	i = 0;
	if (str[i] == PIPE)
	{
		printf("bash: syntax error near unexpected token `|'\n");
		return (ERROR);
	}
	while (str[i])
	{
		if (str[i] == PIPE && str[i + 1] == PIPE)
		{
			printf("bash: syntax error near unexpected token `||'\n");
			return (ERROR);
		}
		i++;
	}
	if (str[i - 1] == PIPE)
	{
		printf("bash: syntax error near unexpected token `|'\n");
		return (ERROR);
	}
	return (NO_ERROR);
}

/*
The following function checks if there are pipes and redirects put together
*/
/*
static int	check_pipe_and_redir(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i]) 
		i++;
	}
	return (NO_ERROR);
}*/
