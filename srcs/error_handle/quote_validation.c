/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:17:04 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/21 17:45:36 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	change_single_quotes(char *str);
static int	multiple_of_2_quotes(char *str);

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
		g_status(MISUSE);
		print_error("minishell: syntax error without quotes closure\n");
		return (ERROR);
	}
	return (NO_ERROR);
}

int	dollar_is_closed_by_quote(char **str, int quote)
{
	int			i;
	int			quote_index;
	enum e_flag quote_flag;

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
		//	remove_quote(str, quote_index, quote);		// Isso aqui era p q?
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	remove_closed_in_quotes_metas(char *str)
{
	int			i;
	enum e_flag double_quote;
	enum e_flag single_quote;

	i = 0;
	double_quote = OFF;
	single_quote = OFF;
	while (str[i])
	{
		if (str[i] == DOUBLE_QUOT_MARK && double_quote == OFF && single_quote == OFF)
			double_quote = ON;
		else if (str[i] == SIMPLE_QUOT_MARK && single_quote == OFF && double_quote == OFF)
			single_quote = ON;
		else if (str[i] == DOUBLE_QUOT_MARK && double_quote == ON)
			double_quote = OFF;
		else if (str[i] == SIMPLE_QUOT_MARK && single_quote == ON)
			single_quote = OFF;
		else if (str[i] == PIPE && (double_quote == ON || single_quote == ON))
			str[i] = UNPRINT_PIPE;
		else if (str[i] == LESS_THAN && (double_quote == ON || single_quote == ON))
			str[i] = UNPRINT_LT;
		else if (str[i] == GREATER_THAN && (double_quote == ON || single_quote == ON))
			str[i] = UNPRINT_GT;
		i++;
	}
}

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
		if (str[i] == DOUBLE_QUOT_MARK && double_quote == OFF && simple_quote == OFF)
			double_quote = ON;
		else if (str[i] == SIMPLE_QUOT_MARK && simple_quote == OFF && double_quote == OFF)
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
		if (str[i] == DOUBLE_QUOT_MARK && double_quote == OFF && simple_quote == OFF)
			double_quote = ON;
		else if (str[i] == SIMPLE_QUOT_MARK && simple_quote == OFF && double_quote == OFF)
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
	if (counter > 3  && counter % 2 == 0)
		return (TRUE);
	return (FALSE);
}