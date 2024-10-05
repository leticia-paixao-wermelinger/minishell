/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:06:43 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/05 00:38:47 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_last_node(t_node *node)
{
    if (node->next == NULL)
        return (TRUE);
    return (FALSE);
}

void    run_pipe_builtin(t_command *command, t_node *node)
{
    t_node  *temp;

    do_dup2(node);
    temp = node;
    close_node_fds(temp);
    run_builtin(command, node->token, command->my_env, node->fd_out);
}
    /*if (is_last_node(node) == TRUE)
            run_builtin(command, node->token, command->my_env, node->fd_out);
    else
            run_builtin(command, node->token, command->my_env, node->next->fd_in);*/

int    pipe_execution(t_command *command, t_node *node)
{
    node->pid = fork();
    if (node->pid == 0)
    {
        if (node->token->type == BUILTIN)
            run_pipe_builtin(command, node);
        else
            run_pipe_execve(command, node);
    g_status(NO_ERROR);
    return (NO_ERROR);
	//exit(g_status(NO_ERROR));
    }
    return (ERROR);
}
