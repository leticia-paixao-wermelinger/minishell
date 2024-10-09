/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:06:43 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/09 19:03:18 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int    run_pipe_execve(t_command *command, t_node *list)
{
    t_node      *node;
    char        *path;
    char        **env_array;
    char        **args;

    node = list;
    env_array = envp_list_to_array(command->my_env);
    if (access(node->token->word, (F_OK | X_OK)) != 0)
    {
        if (errno == EACCES)
            return (close_node_fds(list), free_matrix(env_array), print_errno(node), ERROR);
        path = get_executable_path(command, node);
        if (!path)
            return (close_node_fds(list), free_matrix(env_array), ERROR);
    }
    else
        path = node->token->word;
    args = cmd_list_to_array(node);
    do_dup2(node);
    close_all_node_fds(node);
    execve(path, args, env_array);
    if (path != node->token->word)
        free(path);
    execve_clean(args, env_array);
    exit(0);
}

void    run_pipe_builtin(t_command *command, t_tokens *token, t_env *env, int fd)
{
	if (my_strcmp(token->word, "echo") == 0)
		exit(my_echo(token->next, fd));
	else if (my_strcmp(token->word, "cd") == 0)
		exit(my_cd(token->next, env));
	else if (my_strcmp(token->word, "pwd") == 0)
		exit(pwd());
	else if (my_strcmp(token->word, "export") == 0)
		my_export(env, token->next, fd);
	else if (my_strcmp(token->word, "unset") == 0)
		my_unset(env, token->next);
	else if (my_strcmp(token->word, "env") == 0)
		print_env(env, fd);
	else if (my_strcmp(token->word, "exit") == 0)
		exit(my_exit(token->next, command));
}

void    pipe_execution(t_command *command, t_node *node)
{
    node->pid = fork();
    if (node->pid == 0)
    {
        if (node->token->type != BUILTIN)
            run_pipe_execve(command, node);
        else
            run_pipe_builtin(command, node->token, command->my_env, node->fd_out);
        /*if (node->fd_in != STDIN_FILENO)
        {
            dup2(node->fd_in, STDIN_FILENO);
            close(node->fd_in);
        }
        if (node->fd_out != STDOUT_FILENO)
        {
            dup2(node->fd_out, STDOUT_FILENO);
            close(node->fd_out);
        }*/
        exit(node->exit_status);
    }
    else
    {
        if (node->fd_in != STDIN_FILENO)
            close(node->fd_in);
        if (node->fd_out != STDOUT_FILENO)
            close(node->fd_out);
    }
    return ;
}
