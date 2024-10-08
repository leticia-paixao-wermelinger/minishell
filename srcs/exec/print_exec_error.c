/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_exec_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 11:16:02 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/07 19:37:36 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void print_errno(t_node *node)
{
    if (node && node->token && node->token->word)
    {
        print_error("minishell: ");
        print_error(node->token->word);
        if (errno == EACCES)
        {
            print_error(": Permission denied\n");
            node->exit_status = 126;
            //g_status(126);
        }
        else
        {
            print_error(": Command not found\n");
            node->exit_status = 127;
		    //g_status(127);
        }
    }
    return ;
}
