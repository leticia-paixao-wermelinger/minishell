/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_chars_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:43:07 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/14 23:13:26 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief is_pipe - Checks if a character is a pipe symbol.
 *
 * This function verifies if the given character is a pipe symbol ('|'),
 * which is used in shell commands to indicate piping between processes.
 * This is crucial for parsing command lines in the minishell.
 *
 * @param c: The character to be checked.
 *
 * @return int: Returns TRUE if the character is a pipe, otherwise
 *              returns FALSE.
 */

int	is_pipe(char c)
{
	if (c == '|')
		return (TRUE);
	return (FALSE);
}

/**
 * @brief is_simple_quote - Checks if a character is a single quote.
 *
 * This function checks if the provided character is a single quote
 * ('), which is used in shell commands to denote literal strings
 * where variables are not expanded. This is important for the proper
 * parsing of user input in the minishell.
 *
 * @param c: The character to be checked.
 *
 * @return int: Returns TRUE if the character is a single quote,
 *              otherwise returns FALSE.
 */

int	is_simple_quote(char c)
{
	if (c == '\'')
		return (TRUE);
	return (FALSE);
}

/**
 * @brief is_double_quote - Checks if a character is a double quote.
 *
 * This function checks if the provided character is a double quote
 * ("), which is used in shell commands to denote strings where
 * variables can be expanded. This is critical for parsing and
 * interpreting commands correctly in the minishell.
 *
 * @param c: The character to be checked.
 *
 * @return int: Returns TRUE if the character is a double quote,
 *              otherwise returns FALSE.
 */

int	is_double_quote(char c)
{
	if (c == '\"')
		return (TRUE);
	return (FALSE);
}

/**
 * @brief is_append - Checks if a string represents the append operator.
 *
 * This function checks if the given string is the append operator
 * (">>"). In shell commands, this operator is used to append output
 * to a file. This function is essential for the redirection
 * functionality of the minishell.
 *
 * @param s: The string to be checked.
 *
 * @return int: Returns TRUE if the string is the append operator,
 *              otherwise returns FALSE.
 */

int	is_append(char *s)
{
	if (my_strcmp(s, ">>") == 0)
		return (TRUE);
	return (FALSE);
}

/**
 * @brief is_valid_exp_char - Validates if a character is a valid
 *                            expansion character.
 *
 * This function checks if the given character is valid for variable
 * expansion in shell commands. Valid characters include alphanumeric
 * characters and underscores, which are permitted in variable names.
 * This is important for ensuring that user input conforms to shell
 * syntax in the minishell.
 *
 * @param c: The character to be checked.
 *
 * @return int: Returns TRUE if the character is valid for variable
 *              expansion, otherwise returns FALSE.
 */

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
