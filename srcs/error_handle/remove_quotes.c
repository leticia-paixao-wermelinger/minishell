/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:49:42 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/15 17:08:48 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void remove_quote_2(char *temp, char **str);
int quote_is_valid(char *str, int j, int quote);

void	remove_all_quotes(t_node *list, int quote)
{
	t_node		*node;
	t_tokens	*token;
	int			i;

	node = list;
	while (node)
	{
		token = node->token;
		while (token)
		{
			i = 0;
			while (token->word[i])
			{
				if (token->word[i] == quote && quote_is_valid(token->word, i, quote) == TRUE)
					remove_quote(&(token->word), i, quote);
				i++;
			}
			token = token->next;
		}
		node = node->next;
	}
}

int	quote_is_valid(char *str, int j, int quote)
{
	int				i;
	int				sec_quote;
	enum e_flag		sec_flag;

	i = 0;
	sec_flag = OFF;
	if (quote == DOUBLE_QUOT_MARK)
		sec_quote = SIMPLE_QUOT_MARK;
	else if (quote == SIMPLE_QUOT_MARK)
		sec_quote = DOUBLE_QUOT_MARK;
	while (str[i] && i < j)
	{
		if (str[i] == sec_quote && sec_flag == OFF)
			sec_flag = ON;
		else if (str[i] == sec_quote && sec_flag == ON)
			sec_flag = OFF;
		i++;
	}
	if (sec_flag == ON)
		return (FALSE);
	return (TRUE);
}

void	remove_quote(char **str, int i, enum e_ascii quote)
{
	char	*first;
	char	*temp;
	char	*seccond;
	
	first = NULL;
	temp = fromstrldup(*str, i); 
	seccond = my_strcdup(temp, quote);
	free(temp);
	if (i != 0)
	{
		first = my_strldup(*str, i);
		temp = my_strjoin(first, seccond);
	}
	else
		temp = my_strdup(seccond);
	free(first);
	free(seccond);
	remove_quote_2(temp, str);
}

static void	remove_quote_2(char *temp, char **str)
{
	int		j;
	char	*last;

	last = NULL;
	j = my_strlen(temp);
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
