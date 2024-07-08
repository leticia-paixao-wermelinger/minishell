/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metacharacters_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:54:47 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/07/08 20:57:16 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_metachar(char c)
{
	if (c == PIPE || c == LESS_THAN || c == GREATER_THAN)
		return (TRUE);
	return (FALSE);
}

char	*check_invalid_successive_metachars(char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (is_metachar(input[i]) == TRUE)
		{
			i++;
			while (input[i + j] == SPACE_CHAR)
			{
				j++;
				if (is_metachar(input[i + j]) == TRUE)
				{
					if (input[i] == LESS_THAN && input[i + j] == LESS_THAN)
					
						break ;
				}
			}
			i += j;
			j = 0;
		}
		i++;
	}
	return (input);
}

void	malloc_str_of_invalid_metas(t_command *command)
{
	int	i;
	int	count;
	int	flag_double;
	int	flag_simple;

	i = 0;
	count = 0;
	flag_double = OFF;
	flag_simple = OFF;
	while (command->input[i])
	{
		if (command->input[i] == DOUBLE_QUOT_MARK && flag_double == OFF)
			flag_double = ON;
		else if (command->input[i] == SIMPLE_QUOT_MARK && flag_simple == OFF)
		    flag_simple = ON;
		else if (is_metachar(command->input[i]) == TRUE && (flag_double == ON || flag_simple == ON))
			count++;
		else if (command->input[i] == DOUBLE_QUOT_MARK && flag_double == ON)
			flag_double = OFF;
		else if (command->input[i] == SIMPLE_QUOT_MARK && flag_simple == ON)
			flag_simple = OFF;
		i++;
	}
	command->invalid_metas = (char *)malloc((count + 1) * sizeof(char));
	command->invalid_metas[count + 1] = '\0';
}

void	add_meta_to_metastring(t_command *command, int i)
{
	static int	j = 0;

	command->invalid_metas[j] = command->input[i];
	j++;
}
