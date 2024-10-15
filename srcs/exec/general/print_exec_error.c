/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_exec_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 11:16:02 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/14 23:03:02 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * @brief print_errno - Prints an error message based on the command's
 *                     exit status.
 *
 * This function checks if the command in the provided node has a
 * valid token. If so, it prints a specific error message based
 * on the value of `errno`. It handles permission issues and
 * command not found errors, updating the exit status of the node
 * accordingly.
 *
 * It utilizes the following macros:
 *
 * - `print_error`: A function that simplifies error message printing
 *   to the standard error output. This macro likely handles the
 *   formatting of the error message and ensures it is sent to the
 *   appropriate output stream.
 *
 * @param node: A pointer to the command node that contains the
 *              token to be evaluated for error reporting.
 *
 * @return void: This function does not return a value.
 *
 * @note If `errno` indicates a permission denied error (`EACCES`),
 *       the exit status of the node is set to 126. If the command
 *       is not found, the exit status is set to 127.
 *
 * @see errno: A global variable set by system calls and some library
 *             functions in the event of an error to indicate what
 *             went wrong.
 */

void	print_errno(t_node *node)
{
	if (node && node->token && node->token->word)
	{
		print_error("minishell: ");
		print_error(node->token->word);
		if (errno == EACCES)
		{
			print_error(": Permission denied\n");
			node->exit_status = 126;
		}
		else
		{
			print_error(": Command not found\n");
			node->exit_status = 127;
		}
	}
	return ;
}
