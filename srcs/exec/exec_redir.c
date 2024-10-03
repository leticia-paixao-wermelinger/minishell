/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 00:02:35 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/03 19:19:49 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int has_redirect_or_not(t_node *sentence)
{
    t_node *current_node;

    current_node = sentence;
    while (current_node)
    {
        // Exibe o valor atual do token->type para depuração
        printf("Token type: %d\n", current_node->token->type);

        if (current_node->token->type == REDIR_APPEND ||
            current_node->token->type == REDIR_OUT ||
            current_node->token->type == REDIR_IN ||
            current_node->token->type == REDIR_HEREDOC)
        {
            return (TRUE);
        }
        current_node = current_node->next;
    }
    printf("Não tem redirect!\n");
    return (FALSE);
}

