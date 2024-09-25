/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:21:21 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/25 16:49:28 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char *add_space(char **s, int i);

char	**fix_lack_of_spaces(char **str)
{
	int			i;
	enum e_flag double_quote;
	enum e_flag simple_quote;

	i = 0;
	double_quote = OFF;
	simple_quote = OFF;
	while ((*str)[i])
	{
		if ((*str)[i] == DOUBLE_QUOT_MARK && double_quote == OFF && simple_quote == OFF)
			double_quote = ON;
		else if ((*str)[i] == SIMPLE_QUOT_MARK && simple_quote == OFF && double_quote == OFF)
			simple_quote = ON;
		else if ((*str)[i] == DOUBLE_QUOT_MARK && double_quote == ON)
			double_quote = OFF;
		else if ((*str)[i] == SIMPLE_QUOT_MARK && simple_quote == ON)
			simple_quote = OFF;
		else if (((*str)[i] == REDIR_OUT || (*str)[i] == REDIR_IN) && double_quote == OFF && simple_quote == OFF)
		{
			if ((*str)[i + 1] != SPACE_CHAR && (*str)[i + 1] != (*str)[i] && (*str)[i + 1] != '\0')
				*str = add_space(str, i);
		}
		i++;
	}
	return (str);
}

static char	*add_space(char **s, int i)
{
	char	*first;
	char	*seccond;
	char	*last;
	char	*temp;

	first = my_strldup(*s, i + 1);
	seccond = my_calloc(2, sizeof(char));
	seccond[0] = ' ';
	seccond[1] = '\0';
	last = fromstrldup(*s, i);
	printf("s: |%s|\n", *s);
	printf("first: |%s|; seccond: |%s|; last: |%s|\n", first, seccond, last);
	free(*s);
	*s = NULL;
	temp = my_strjoin(first, seccond);
	free(first);
	free(seccond);
	*s = my_strjoin(temp, last);
	free(temp);
	free(last);
	printf("s retornado: |%s|\n", *s);
	return (*s);
}
