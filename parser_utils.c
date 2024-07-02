/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:59:20 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/07/01 20:47:21 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strlen_without_spaces_post_metachars(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (is_metachar(s[i]) == TRUE)
		{
			i++;
			count++;
			while (s[i] == SPACE_CHAR)
				i++;
		}
		count++;
		i++;
	}
	return (count);
}

int	strlen_without_spaces_before_metachars(char *s)
{
	int	i;
	int	count;

	i = my_strlen(s);
	count = 0;
	while (i >= 0)
	{
		if (is_metachar(s[i]) == TRUE)
		{
			i--;
			count++;
			while ((i >= 0) && (s[i] == SPACE_CHAR))
				i--;
		}
		count++;
		i--;
	}
	return (count);
}
/*
int	strlen_without_spaces_around_metachars(char *s)
{
	int	i;
	int	count;
	int	flag_meta;

	i = 0;
	count = i;
	flag_meta = OFF;
	while (s[i])
	{
		if (s[i] == SPACE_CHAR)
			flag_meta = ON;
		else
			flag_meta = OFF;
		if (is_metachar(s[i]) == TRUE)
		{
			i++;
			count++;
			while (s[i] == SPACE_CHAR)
				i++;
		}
		count++;
		i++;
	}
}*/
