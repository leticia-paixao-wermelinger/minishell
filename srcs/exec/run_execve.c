/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:11:22 by lraggio           #+#    #+#             */
/*   Updated: 2024/09/27 21:54:32 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int    run_execve(t_command *command, t_node *list)
{
    int     exit_status;
    t_node      *node;
    pid_t       pid;
    char        *path;
    char        **env_array;
    char        **args;

    exit_status = g_status(-1);
    env_array = envp_list_to_array(command->my_env);
    path = get_executable_path(command, list);
    node = list;
    args = cmd_list_to_array(node);
    pid = fork();
    if (pid == 0) //child proccess
    {
        pid = list->pid;
        if (execve(path, args, env_array) == -1)
        	return (execve_clean(path, env_array, command), free_matrix(args), g_status(127), ERROR);
    }
    waitpid(list->pid, &exit_status, 0);
    return (execve_clean(path, env_array, command), free_matrix(args), NO_ERROR);
}
