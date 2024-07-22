/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metacharacters_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:54:47 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/07/21 20:10:12 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_metachar(char c)
{
	if (c == PIPE || c == LESS_THAN || c == GREATER_THAN)
		return (TRUE);
	return (FALSE);
}
/*
char	*check_invalid_successive_metachars(char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (is_metachar(input[i]) == TRUE)
		{
			i++;
			while (input[i + j] == SPACE_CHAR)
			{
				j++;
				if (is_metachar(input[i + j]) == TRUE)
				{
					if (input[i] == LESS_THAN && input[i + j] == LESS_THAN)
					
						break ;
				}
			}
			i += j;
			j = 0;
		}
		i++;
	}
	return (input);
}
*/
