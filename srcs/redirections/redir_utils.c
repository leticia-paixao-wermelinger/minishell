/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 09:16:50 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/26 00:51:40 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_permissions(char *pathname, int flag)
{
	if (access(pathname, flag) < 0)
	{
		permission_denied(pathname);
		return (ERROR);
	}
	return (NO_ERROR);
}

void	remove_redir_nodes(t_node *sentence, t_tokens *redir_node)
{
	t_tokens    *temp;

	temp = NULL;
	if (sentence->token == redir_node)
		temp = redir_node->next->next;
	remove_word_token(redir_node->next, sentence->token, sentence);
	remove_word_token(redir_node, sentence->token, sentence);
	if (temp != NULL)
		sentence->token = temp;
	if (!sentence->token)
		sentence->token = NULL;
}