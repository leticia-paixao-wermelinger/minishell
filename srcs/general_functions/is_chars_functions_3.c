/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_chars_functions_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:13:44 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/10/14 23:14:31 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief is_char - Checks if two characters are equal.
 *
 * This function compares two characters to determine if they are the same.
 * It is a simple utility function that can be used in various contexts
 * within the minishell, such as checking for specific characters
 * during command parsing or handling user input.
 *
 * @param o: The first character to be compared.
 * @param c: The second character to be compared.
 *
 * @return int: Returns TRUE if the characters are equal, otherwise
 *              returns FALSE.
 */

int	is_char(char o, char c)
{
	if (o == c)
		return (TRUE);
	return (FALSE);
}
