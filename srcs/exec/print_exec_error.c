/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_exec_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 11:16:02 by lraggio           #+#    #+#             */
/*   Updated: 2024/09/29 23:44:34 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void print_permission_denied(t_node *node)
{
	extern volatile unsigned int	g_status;

    if (node && node->token && node->token->word)
    {
        print_error("minishell: ");
        print_error(node->token->word);
        print_error(": Permission denied\n");
		g_status = 126;
    }
}

void print_cmd_not_found(t_node *node)
{
	extern volatile unsigned int	g_status;

    if (node && node->token && node->token->word)
    {
        print_error("minishell: ");
        print_error(node->token->word);
        print_error(": command not found\n");
		g_status = 127;
    }
}
