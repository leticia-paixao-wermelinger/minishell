/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:06:43 by lraggio           #+#    #+#             */
/*   Updated: 2024/09/27 21:53:11 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*

Função p/ percorrer node e organizar os fds

void    clean_pipe(t_node *node)
{
    free_list(node);
}
*/

int     pipe_execution(t_command *command, t_node *node)
{
    int     exit_status;
    int     pipe_fd[2];
    int     pid_1;
    int     pid_2;

    exit_status = g_status(-1);
    if (pipe(pipe_fd) == -1)
        return (perror(strerror(errno)), ERROR);
    pid_1 = fork();
    if (pid_1 == -1)
        return (perror("fork"), ERROR);
    if (pid_1 == 0)
    {
        close(pipe_fd[0]);
        if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
        {

            perror("dup2 (stdout)");
            exit(ERROR);
        }
        close(pipe_fd[1]);
        run_commands(command, node);
        exit(EXIT_SUCCESS);
    }
    pid_2 = fork();
    if (pid_2 == -1)
        return (perror("fork"), ERROR);

    if (pid_2 == 0)
    {
        close(pipe_fd[1]);
        if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
        {
            perror("dup2 (stdin)");
            exit(ERROR);
        }
        close(pipe_fd[0]);
        run_commands(command, node);
        exit(EXIT_SUCCESS);
    }
    close_fds(pipe_fd[0], pipe_fd[1]);
    waitpid(pid_1, &exit_status, 0);
    waitpid(pid_2, &exit_status, 0);
    return (NO_ERROR);
}
