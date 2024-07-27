/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_of_invalid_metas.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:33:14 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/07/26 23:06:44 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

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
	command->invalid_metas[count] = '\0';
}

void	add_meta_to_metastring(t_command *command, int i)
{
	static int	j = 0;

	command->invalid_metas[j] = command->input[i];
	j++;
}
