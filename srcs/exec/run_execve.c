/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:11:22 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/04 17:49:01 by lraggio          ###   ########.fr       */
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

    node = list;
    env_array = envp_list_to_array(command->my_env);
    if (access(node->token->word, (F_OK | X_OK)) != 0)
    {
        if (errno == EACCES)
            return (print_errno(node));
        path = get_executable_path(command, node);
        if (!path)
        {
            free_matrix(env_array);
            return ;
        }
    }
    else
        path = node->token->word;
    args = cmd_list_to_array(node);
    node->pid = fork();
    if (node->pid == 0)
    {
        do_dup2(node);
        temp = node;
        close_node_fds(temp);
        execve(path, args, env_array);

    }
    if (path != node->token->word)
        free(path);
    execve_clean(args, env_array);
    return ;
}

void    run_pipe_execve(t_command *command, t_node *list)
{
    t_node      *node;
    t_node      *temp;
    char        *path;
    char        **env_array;
    char        **args;

    node = list;
    env_array = envp_list_to_array(command->my_env);
    if (access(node->token->word, (F_OK | X_OK)) != 0)
    {
        if (errno == EACCES)
            return (print_errno(node));
        path = get_executable_path(command, node);
        if (!path)
        {
            free_matrix(env_array);
            return ;
        }
    }
    else
        path = node->token->word;
    args = cmd_list_to_array(node);
    do_dup2(node);
    temp = node;
    close_node_fds(temp);
    execve(path, args, env_array);
    if (path != node->token->word)
        free(path);
    execve_clean(args, env_array);
    return ;
}
