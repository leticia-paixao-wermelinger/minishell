/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_chars_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:43:07 by lraggio           #+#    #+#             */
/*   Updated: 2024/08/12 21:34:39 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/*
int is_space_or(char c)
{
    return (c == ' ' || c == '\t');
}
*/
