/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:17:04 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/15 12:08:20 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
			remove_simple_quote(str, quote_index);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

void	remove_simple_quote(char **str, int i)
{
	char	*first;
	char	*temp;
	char	*seccond;
	char	*last;
	int		j;
	
	first = NULL;
	last = NULL;
	temp = fromstrldup(*str, i); 
	seccond = my_strcdup(temp, SIMPLE_QUOT_MARK);
	free(temp);
	if (i != 0)
	{
		first = my_strldup(*str, i);
		temp = my_strjoin(first, seccond);
	}
	else
		temp = my_strdup(seccond);
	j = my_strlen(temp);
	free(first);
	free(seccond);
	if ((*str)[j + 2] != '\0')
	{
		last = fromstrldup(*str, j + 1);
		free(*str);
		*str = NULL;
		*str = my_strjoin(temp, last);
	}
	else
	{
		free(*str);
		*str = NULL;
		*str = my_strdup(temp);
	}
	free(temp);
	free(last);
}
