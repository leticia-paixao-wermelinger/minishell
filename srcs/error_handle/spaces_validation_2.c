/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces_validation_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 22:53:54 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/15 00:38:46 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*add_space_after(char *s, int i);
static char	*add_space_before(char *s, int i);

/**
 * @brief fix_lack_of_spaces - Ensures proper spacing around redirection tokens.
 *
 * This function adds spaces before and after redirection operators
 * in the string to ensure that they are properly spaced from other
 * tokens. It modifies the input string as needed.
 *
 * @param str: The input string to be modified.
 *
 * @return char*: The modified string with appropriate spaces.
 */

char	*fix_lack_of_spaces(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == REDIR_OUT || str[i] == REDIR_IN)
		{
			if (str[i + 1] != SPACE_CHAR && str[i + 1] != str[i]
				&& str[i + 1] != '\0')
				str = add_space_after(str, i);
		}
	}
	while (--i > 0)
	{
		if (str[i] == REDIR_OUT || str[i] == REDIR_IN)
		{
			if (str[i - 1] != SPACE_CHAR && str[i - 1] != str[i]
				&& str[i - 1] != '\0')
				str = add_space_before(str, i);
		}
	}
	return (str);
}

/**
 * @brief add_space_after - Adds a space after a specified index in a string.
 *
 * This helper function creates a new string by adding a space after
 * the character at the specified index. It handles memory management
 * to ensure no memory leaks occur.
 *
 * @param s: The original string to modify.
 * @param i: The index after which to add a space.
 *
 * @return char*: The new string with a space added.
 */

static char	*add_space_after(char *s, int i)
{
	char	*first;
	char	*seccond;
	char	*last;
	char	*temp;

	first = my_strldup(s, i + 1);
	seccond = my_calloc(2, sizeof(char));
	seccond[0] = ' ';
	seccond[1] = '\0';
	last = fromstrldup(s, i);
	temp = my_strjoin(first, seccond);
	free(first);
	free(seccond);
	free(s);
	s = my_strjoin(temp, last);
	free(temp);
	free(last);
	return (s);
}

/**
 * @brief add_space_before - Adds a space before a specified index in a string.
 *
 * This helper function creates a new string by adding a space before
 * the character at the specified index. It manages memory to prevent
 * leaks.
 *
 * @param s: The original string to modify.
 * @param i: The index before which to add a space.
 *
 * @return char*: The new string with a space added.
 */

static char	*add_space_before(char *s, int i)
{
	char	*first;
	char	*seccond;
	char	*last;
	char	*temp;

	first = my_strldup(s, i);
	seccond = my_calloc(2, sizeof(char));
	seccond[0] = ' ';
	seccond[1] = '\0';
	last = fromstrldup(s, i - 1);
	temp = my_strjoin(first, seccond);
	free(first);
	free(seccond);
	free(s);
	s = my_strjoin(temp, last);
	free(temp);
	free(last);
	return (s);
}
