/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 00:02:35 by lraggio           #+#    #+#             */
/*   Updated: 2024/09/30 00:09:34 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int has_redirect_or_not(t_node *sentence)
{
    t_node *current_node;

    current_node = sentence;
    while (current_node)
    {
        if (current_node->token->type == REDIR_APPEND)
            return (TRUE);
        if (current_node->token->type == REDIR_OUT)
            return (TRUE);
        if (current_node->token->type == REDIR_IN)
            return (TRUE);
        if (current_node->token->type == REDIR_HEREDOC)
            return (TRUE);
        current_node = current_node->next;
    }
    return (FALSE);
}
