/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_chars_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:43:07 by lraggio           #+#    #+#             */
/*   Updated: 2024/09/03 15:39:33 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_pipe(char c)
{
	if (c == '|')
		return (TRUE);
	return (FALSE);
}

int is_simple_quote(char c)
{
	if (c == '\'')
		return (TRUE);
	return (FALSE);
}

int is_double_quote(char c)
{
	if (c == '\"')
		return (TRUE);
	return (FALSE);
}

int	is_append(char *s)
{
	if (my_strcmp(s, ">>") == 0)
		return (TRUE);
	return (FALSE);
}

int	is_valid_exp_char(char c)
{
	if (c >= '0' && c <= '9')
	{
		printf("|%c| é um número\n", c);
		return (TRUE);
	}
	else if (c >= 'A' && c <= 'Z')
	{
		printf("|%c| é uma letra maiúscula\n", c);
		return (TRUE);
	}
	else if (c >= 'a' && c <= 'z')
	{
		printf("|%c| é uma letra minúscula\n", c);
		return (TRUE);
	}
	else if (c == '_')
	{
		printf("|%c| é um underline\n", c);
		return (TRUE);
	}
	return (FALSE);
}

/*
int	is_char(char *s, char c)
{
	if (my_strcmp(s, c) == 0)
		return (TRUE);
	return (FALSE);
}
*/

int is_char(char o, char c)
{
	if (o == c)
		return (TRUE);
	return (FALSE);
}
