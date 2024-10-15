/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_general_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:43:21 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/10/14 19:11:52 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * print_error - Outputs an error message to the standard error.
 *
 * This function takes a string as input and prints it to the standard
 * error output (file descriptor 2) using the my_putstr_fd function.
 *
 * @param str: The error message string to be printed.
 *
 * @return void: This function does not return a value.
 */

void	print_error(char *str)
{
	my_putstr_fd(str, 2);
}

/**
 * no_such_file - Reports a "No such file or directory" error.
 *
 * This function prints an error message indicating that the specified
 * file or directory does not exist. It prefixes the message with
 * "minishell: " and appends the appropriate error description.
 *
 * @param str: The name of the file or directory that was not found.
 *
 * @return int: Returns ERROR to indicate that the error has occurred.
 */

int	no_such_file(char *str)
{
	print_error("minishell: ");
	print_error(str);
	print_error(": No such file or directory\n");
	g_status(ERROR);
	return (ERROR);
}

/**
 * permission_denied - Reports a "Permission denied" error.
 *
 * This function prints an error message indicating that permission is
 * denied for the specified file or directory. It prefixes the message
 * with "minishell: " and appends the appropriate error description.
 *
 * @param str: The name of the file or directory for which permission is
 *             denied.
 *
 * @return int: Returns ERROR to indicate that the error has occurred.
 */

int	permission_denied(char *str)
{
	print_error("minishell: ");
	print_error(str);
	print_error(": Permission denied\n");
	g_status(ERROR);
	return (ERROR);
}

/**
 * print_no_such_file - Reports a "No such file or directory" error for 
 *                      a given command-line argument.
 *
 * This function takes an array of strings (argv) and prints an error
 * message indicating that the file or directory specified in argv[1]
 * does not exist. It prefixes the message with "minishell: ".
 *
 * @param argv: An array of command-line arguments, where argv[1] 
 *               contains the name of the file or directory that was 
 *               not found.
 *
 * @return void: This function does not return a value.
 */

void	print_no_such_file(char **argv)
{
	print_error("minishell: ");
	print_error(argv[1]);
	print_error(": No such file or directory\n");
}

/**
 * print_heredoc_ctrld - Prints a warning message for a here-document
 *                       delimited by end-of-file.
 *
 * This function prints a warning message indicating that a here-document
 * was terminated by an end-of-file (EOF) instead of the expected delimiter.
 * It includes the line number of the here-document in the warning.
 *
 * @param count: The line number of the here-document.
 * @param delimiter: The expected delimiter for the here-document.
 *
 * @return void: This function does not return a value.
 */

void	print_heredoc_ctrld(int count, char *delimiter)
{
	char	*number;

	number = my_itoa(count);
	print_error("minishell: warning: here-document at line ");
	print_error(number);
	print_error(" delimited by end-of-file (wanted `");
	print_error(delimiter);
	print_error("')\n");
	free(number);
}