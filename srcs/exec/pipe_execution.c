/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:06:43 by lraggio           #+#    #+#             */
/*   Updated: 2024/09/28 19:35:39 by lraggio          ###   ########.fr       */
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

    if (node->fd_in != STDIN_FILENO)
        dup2(node->fd_in, 0);
    if (node->fd_out != STDOUT_FILENO)
        dup2(node->fd_out, 0);
    temp = node;
    close_node_fds(temp);
    if (is_last_node(node) == TRUE)
            run_builtin(command, node->token, command->my_env, STDOUT_FILENO);
    else
        run_builtin(command, node->token, command->my_env, node->next->fd_in);
}

int    pipe_execution(t_command *command, t_node *node)
{
    node->pid = fork();
    if (node->pid == 0)
    {
        if (node->token->type == BUILTIN)
            run_pipe_builtin(command, node);
        else
            run_pipe_execve(command, node);
        exit(NO_ERROR);
    }
    return (ERROR);
}
