/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_chars_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:43:07 by lraggio           #+#    #+#             */
/*   Updated: 2024/09/18 17:18:19 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_pipe(char c)
{
	if (c == '|')
		return (TRUE);
	return (FALSE);
}

int	is_simple_quote(char c)
{
	if (c == '\'')
		return (TRUE);
	return (FALSE);
}

int	is_double_quote(char c)
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
		return (TRUE);
	else if (c >= 'A' && c <= 'Z')
		return (TRUE);
	else if (c >= 'a' && c <= 'z')
		return (TRUE);
	else if (c == '_')
		return (TRUE);
	return (FALSE);
}
