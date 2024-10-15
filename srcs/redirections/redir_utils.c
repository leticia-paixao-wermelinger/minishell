/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 09:16:50 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/10/14 23:51:26 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Check the permissions of a given pathname.
 *
 * This function checks if the process has the specified permissions
 * for the given pathname using the `access` system call. If the permissions
 * are denied, it calls `permission_denied` to handle the error.
 *
 * @param pathname The path to the file or directory to check permissions for.
 * @param flag An integer representing the type of permission to check:
 *             - R_OK: Read permission
 *             - W_OK: Write permission
 *             - X_OK: Execute permission
 *
 * @return An integer indicating the status of the permission check:
 *         - ERROR if permission is denied,
 *         - NO_ERROR if permission is granted.
 */

int	check_permissions(char *pathname, int flag)
{
	if (access(pathname, flag) < 0)
		return (permission_denied(pathname), ERROR);
	return (NO_ERROR);
}

/**
 * @brief Remove redirection nodes from a command's token list.
 *
 * This function removes the specified redirection node and its associated
 * token from the command's token list. It adjusts the linked list accordingly
 * to maintain integrity after the removal.
 *
 * @param sentence A pointer to the command node (`t_node`) from which the
 *                 redirection nodes should be removed.
 * @param redir_node A pointer to the redirection token (`t_tokens`)
 *                   that is to be removed.
 */

void	remove_redir_nodes(t_node *sentence, t_tokens *redir_node)
{
	t_tokens	*temp;

	temp = NULL;
	if (sentence->token == redir_node)
		temp = redir_node->next->next;
	remove_word_token(redir_node->next, sentence->token, sentence);
	remove_word_token(redir_node, sentence->token, sentence);
	if (temp != NULL)
		sentence->token = temp;
	if (!(sentence->token))
		sentence->token = NULL;
}
