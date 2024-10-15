/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_closed_quote_validation.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 22:31:46 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/14 22:38:02 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * remove_closed_in_quotes_metas - Replaces meta characters inside quotes.
 *
 * This function traverses the string `str` and replaces meta characters
 * (such as pipes and redirections) that are enclosed within quotes with
 * special unprintable characters, so they are ignored in parsing.
 *
 * @param str: The input string to process.
 *
 * @return void: This function does not return a value.
 */

void	remove_closed_in_quotes_metas(char *str, enum e_flag double_quote, \
		enum e_flag single_quote)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i] == DOUBLE_QUOT_MARK && double_quote == OFF
			&& single_quote == OFF)
			double_quote = ON;
		else if (str[i] == SIMPLE_QUOT_MARK && single_quote == OFF
			&& double_quote == OFF)
			single_quote = ON;
		else if (str[i] == DOUBLE_QUOT_MARK && double_quote == ON)
			double_quote = OFF;
		else if (str[i] == SIMPLE_QUOT_MARK && single_quote == ON)
			single_quote = OFF;
		else if (str[i] == PIPE && (double_quote == ON || single_quote == ON))
			str[i] = UNPRINT_PIPE;
		else if (str[i] == LESS_THAN && (double_quote == ON
				|| single_quote == ON))
			str[i] = UNPRINT_LT;
		else if (str[i] == GREATER_THAN && (double_quote == ON
				|| single_quote == ON))
			str[i] = UNPRINT_GT;
		i++;
	}
}

/**
 * return_closed_in_quotes_metas - Restores original meta characters.
 *
 * This function restores the original meta characters in the string `str`
 * that were previously replaced by unprintable characters.
 *
 * @param str: The input string to process.
 *
 * @return void: This function does not return a value.
 */

void	return_closed_in_quotes_metas(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == UNPRINT_PIPE)
			str[i] = PIPE;
		else if (str[i] == UNPRINT_GT)
			str[i] = GREATER_THAN;
		else if (str[i] == UNPRINT_LT)
			str[i] = LESS_THAN;
		i++;
	}
}
