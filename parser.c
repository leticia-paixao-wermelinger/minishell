/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:41:24 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/06/28 23:08:53 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_parser(t_command *command)
{
	search_invalid_pipes(command);
	//my_printf("Ajuste pré split: %s\n", command->input);
	//split
	//return_invalid_pipes
}

void	search_invalid_pipes(t_command *command)
{
	int	i;
	int	flag_double;
	int	flag_simple;

	i = 0;
	flag_double = OFF;
	flag_simple = OFF;
	while (command->input[i])
	{
		if (command->input[i] == DOUBLE_QUOT_MARK && flag_double == OFF)
			flag_double = ON;
		else if (command->input[i] == SIMPLE_QUOT_MARK && flag_simple == OFF)
			flag_simple = ON;
		else if (command->input[i] == PIPE && (flag_double == ON || flag_simple == ON))
			command->input[i] = UNPRINT_CHAR;
		else if (command->input[i] == DOUBLE_QUOT_MARK && flag_double == ON)
			flag_double = OFF;
		else if (command->input[i] == SIMPLE_QUOT_MARK && flag_simple == ON)
			flag_simple = OFF;
		i++;
	}
}
