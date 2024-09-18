/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:17:04 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/18 17:18:19 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


extern volatile unsigned int    g_status;

int	n_quote_validation(char *str)
{
	int			i;
	enum e_flag	double_quote;
	enum e_flag	simple_quote;

	i = 0;
	double_quote = OFF;
	simple_quote = OFF;
	while (str[i])
	{
		if (str[i] == DOUBLE_QUOT_MARK && double_quote == OFF && simple_quote == OFF)
			double_quote = ON;
		else if (str[i] == SIMPLE_QUOT_MARK && simple_quote == OFF && double_quote == OFF)
			simple_quote = ON;
		else if (str[i] == DOUBLE_QUOT_MARK && double_quote == ON)
			double_quote = OFF;
		else if (str[i] == SIMPLE_QUOT_MARK && simple_quote == ON)
			simple_quote = OFF;
		i++;
	}
	if (double_quote == ON || simple_quote == ON)
	{
		g_status = MISUSE;
		print_error("bash: syntax error without quotes closure\n");
		return (ERROR);
	}
	return (NO_ERROR);
}

int	dollar_is_closed_by_single_quote(char **str)
{
	int	i;
	int	quote_index;
	enum e_flag simple_quote;

	i = 0;
	simple_quote = OFF;
	while ((*str)[i])
	{
		if ((*str)[i] == SIMPLE_QUOT_MARK && simple_quote == OFF)
		{
			quote_index = i;
			simple_quote = ON;
		}
		if ((*str)[i] == DOLLAR && simple_quote == ON)
		{
			remove_quote(str, quote_index, SIMPLE_QUOT_MARK);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}
