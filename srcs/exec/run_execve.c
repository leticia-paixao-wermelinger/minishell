/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:11:22 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/01 17:06:48 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    run_execve(t_command *command, t_node *list)
{
    t_node      *node;
    t_node      *temp;
    char        *path;
    char        **env_array;
    char        **args;

    env_array = envp_list_to_array(command->my_env);

    if (access(list->token->word, (F_OK | X_OK)) != 0)
    {
        if (errno == EACCES)
            return (print_errno(list));
        path = get_executable_path(command, list);
        if (!path)
        {
            free_matrix(env_array);
            free(path);
            return ;
        }
    }
    else
        path = list->token->word;
    node = list;
    args = cmd_list_to_array(node);
    node->pid = fork();
    if (node->pid == 0)
    {
            if (node->fd_out != STDOUT_FILENO)
            dup2(node->fd_out, STDOUT_FILENO);
        if (node->fd_in != STDIN_FILENO)
            dup2(node->fd_in, STDIN_FILENO);
        temp = node;
        close_node_fds(temp);
        execve(path, args, env_array);
    }
    execve_clean(path, args, env_array);
    return ;
}

void    run_pipe_execve(t_command *command, t_node *list)
{
    t_node      *node;
    t_node      *temp;
    char        *path;
    char        **env_array;
    char        **args;

    env_array = envp_list_to_array(command->my_env);
    if (access(list->token->word, X_OK) != 0) // verificar acesso em outra função mais completa!!!
        path = get_executable_path(command, list);
    else
        path = list->token->word;
    node = list;
    args = cmd_list_to_array(node);
    do_dup2(node);
    temp = node;
    close_node_fds(temp);
    execve(path, args, env_array);
    return ;
}
