/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:17:04 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/10/15 00:39:17 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	change_single_quotes(char *str);
static int	multiple_of_2_quotes(char *str);

/**
 * n_quote_validation - Validates the closure of quotes in a string.
 *
 * This function traverses the string `str` and checks if all single ('') and
 * double quotes ("") are properly closed. If there is a missing closing quote,
 * it prints a syntax error, sets the global status to MISUSE, and returns
 * ERROR.
 *
 * @param str: The input string to be validated for proper quote closure.
 *
 * @return ERROR if quotes are not properly closed.
 *         NO_ERROR if all quotes are properly closed.
 */

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
		if (str[i] == DOUBLE_QUOT_MARK && double_quote == OFF
			&& simple_quote == OFF)
			double_quote = ON;
		else if (str[i] == SIMPLE_QUOT_MARK && simple_quote == OFF
			&& double_quote == OFF)
			simple_quote = ON;
		else if (str[i] == DOUBLE_QUOT_MARK && double_quote == ON)
			double_quote = OFF;
		else if (str[i] == SIMPLE_QUOT_MARK && simple_quote == ON)
			simple_quote = OFF;
		i++;
	}
	if (double_quote == ON || simple_quote == ON)
	{
		g_status(MISUSE);
		print_error("minishell: syntax error without quotes closure\n");
		return (ERROR);
	}
	return (NO_ERROR);
}

/**
 * dollar_is_closed_by_quote - Checks if a dollar sign is inside quotes.
 *
 * This function checks if a dollar sign ('$') in the string is enclosed by
 * quotes. If so, it determines whether the string contains a closing quote.
 *
 * @param str: The string to check.
 * @param quote: The type of quote to check for (single or double).
 *
 * @return TRUE if a dollar sign is enclosed by quotes.
 *         FALSE if there is no enclosing quote for the dollar sign.
 */

int	dollar_is_closed_by_quote(char **str, int quote)
{
	int			i;
	int			quote_index;
	enum e_flag	quote_flag;

	i = 0;
	(void)quote_index;
	quote_flag = OFF;
	while ((*str)[i])
	{
		if ((*str)[i] == quote && quote_flag == OFF)
		{
			quote_index = i;
			quote_flag = ON;
		}
		else if ((*str)[i] == DOLLAR && quote_flag == ON)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

/**
 * single_quotes_to_unprintable - Converts single quotes to unprintable chars.
 *
 * This function converts single quotes within a token's word to unprintable
 * characters if there is an uneven number of quotes.
 *
 * @param list: The linked list of nodes to process.
 *
 * @return void: This function does not return a value.
 */

void	single_quotes_to_unprintable(t_node *list)
{
	t_node		*temp;
	t_tokens	*words;

	temp = list;
	while (temp)
	{
		words = temp->token;
		while (words)
		{
			if (multiple_of_2_quotes(words->word) == FALSE)
				change_single_quotes(words->word);
			words = words->next;
		}
		temp = temp->next;
	}
}

/**
 * change_single_quotes - Replaces single quotes with unprintable characters.
 *
 * This function traverses the string `str` and replaces single quotes with
 * an unprintable character if they are not properly enclosed.
 *
 * @param str: The input string to process.
 *
 * @return void: This function does not return a value.
 */

static void	change_single_quotes(char *str)
{
	int			i;
	enum e_flag	double_quote;
	enum e_flag	simple_quote;

	i = 0;
	double_quote = OFF;
	simple_quote = OFF;
	while (str[i])
	{
		if (str[i] == DOUBLE_QUOT_MARK && double_quote == OFF
			&& simple_quote == OFF)
			double_quote = ON;
		else if (str[i] == SIMPLE_QUOT_MARK && simple_quote == OFF
			&& double_quote == OFF)
		{
			str[i] = UNPRINT_CHAR;
			simple_quote = ON;
		}
		else if (str[i] == DOUBLE_QUOT_MARK && double_quote == ON)
			double_quote = OFF;
		else if (str[i] == SIMPLE_QUOT_MARK && simple_quote == ON)
		{
			str[i] = UNPRINT_CHAR;
			simple_quote = OFF;
		}
		i++;
	}
}

/**
 * multiple_of_2_quotes - Checks if the string has an even number of quotes.
 *
 * This function checks if the string `str` contains an even number of single
 * quotes, indicating that they are properly enclosed.
 *
 * @param str: The input string to check.
 *
 * @return TRUE if the string contains an even number of single quotes.
 *         FALSE if there is an uneven number of single quotes.
 */

static int	multiple_of_2_quotes(char *str)
{
	int			i;
	int			counter;
	enum e_flag	double_quote;
	enum e_flag	simple_quote;

	i = 0;
	counter = 0;
	double_quote = OFF;
	simple_quote = OFF;
	while (str[i])
	{
		if (str[i] == DOUBLE_QUOT_MARK && double_quote == OFF
			&& simple_quote == OFF)
			double_quote = ON;
		else if (str[i] == SIMPLE_QUOT_MARK && simple_quote == OFF
			&& double_quote == OFF)
		{
			counter++;
			simple_quote = ON;
		}
		else if (str[i] == DOUBLE_QUOT_MARK && double_quote == ON)
			double_quote = OFF;
		else if (str[i] == SIMPLE_QUOT_MARK && simple_quote == ON)
		{
			counter++;
			simple_quote = OFF;
		}
		i++;
	}
	if (counter > 3 && counter % 2 == 0)
		return (TRUE);
	return (FALSE);
}
