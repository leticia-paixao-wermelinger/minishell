/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metacharacters_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:54:47 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/07/01 17:55:25 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_metachar(char c)
{
	// SÃO ESSES CARACTERES MESMO??
	if (c == PIPE || c == LESS_THAN || c == GREATER_THAN)
		return (TRUE);
	else if (c == AMPERSAND || c == SEMICOLON || c == OPEN_PARENTHESIS || c == CLOSE_PARENTHESIS)
		return (TRUE);
	return (FALSE);
}
