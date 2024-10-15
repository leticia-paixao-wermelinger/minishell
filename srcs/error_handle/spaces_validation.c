/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:21:21 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/10/14 22:54:44 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*remove_spaces(int flag, char *str, int i);

/**
 * @brief only_spaces - Checks if a string consists only of spaces.
 *
 * This function iterates through the given string to determine if
 * it contains only space characters. If the string is empty or
 * contains only spaces, an error status is set and ERROR is returned.
 *
 * @param str: The input string to check.
 *
 * @return int: Returns ERROR if the string consists only of spaces,
 *              or NO_ERROR otherwise.
 */

int	only_spaces(char *str)
{
	int	i;
	int	size;

	i = 0;
	size = my_strlen(str);
	while (str[i])
	{
		if (str[i] == SPACE_CHAR)
			i++;
		else
			break ;
	}
	if (i == size)
	{
		g_status(NOT_FOUND);
		return (ERROR);
	}
	return (NO_ERROR);
}

/**
 * @brief remove_init_and_end_spaces - Removes leading and trailing spaces.
 *
 * This function removes spaces from the beginning and end of the
 * given string. It checks for leading spaces and removes them,
 * then checks for trailing spaces and removes them as well.
 *
 * @param str: The input string from which spaces will be removed.
 *
 * @return char*: A new string without leading and trailing spaces.
 */

char	*remove_init_and_end_spaces(char *str)
{
	int	i;

	i = 0;
	if (str[i] == SPACE_CHAR)
	{
		while (str[i] == SPACE_CHAR)
			i++;
		str = remove_spaces(1, str, i);
		i = 0;
	}
	while (str[i])
		i++;
	i--;
	if (str[i] == SPACE_CHAR)
	{
		while (i >= 0 && str[i] == SPACE_CHAR)
			i--;
		str = remove_spaces(2, str, i);
	}
	return (str);
}

/**
 * @brief remove_spaces - Helper function to remove spaces from a string.
 *
 * This function removes spaces from the string based on the given
 * flag. It creates a new string without the leading or trailing
 * spaces as specified by the flag.
 *
 * @param flag: Indicates whether to remove leading or trailing spaces.
 * @param str: The input string from which spaces will be removed.
 * @param i: The index at which to remove spaces.
 *
 * @return char*: A new string without the specified spaces.
 */

static char	*remove_spaces(int flag, char *str, int i)
{
	char	*new;

	new = NULL;
	if (flag == 1)
		new = fromstrldup(str, i - 1);
	else
		new = my_strldup(str, i + 1);
	free(str);
	str = NULL;
	return (new);
}
