/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:11:22 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/13 18:06:04 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*check_executable_path(t_command *cmd, t_node *node, char **env_array)
{
	if (access(node->token->word, (F_OK | X_OK)) != 0)
	{
		if (errno == EACCES)
			return (print_errno(node), free_matrix(env_array), NULL);
		return (get_executable_path(cmd, node));
	}
	else
		return (node->token->word);
}

void	run_execve(t_command *command, t_node *list)
{
	t_node		*node;
	char		*path;
	char		**env_array;
	char		**args;

	node = list;
	env_array = envp_list_to_array(command->my_env);
	path = check_executable_path(command, node, env_array);
	if (!path)
		return (free_matrix(env_array));
	args = cmd_list_to_array(node);
	node->pid = fork();
	if (node->pid == 0)
	{
		do_dup2(node);
		close_node_fds(node);
		execve(path, args, env_array);
	}
	if (path != node->token->word)
		free(path);
	return (execve_clean(args, env_array));
}
