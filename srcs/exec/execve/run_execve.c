/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:11:22 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/14 22:59:46 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * @brief check_executable_path - Checks for the executable path of a command.
 *
 * This function verifies if the command specified in the token can be
 * accessed and executed. If the command is not found or is not executable,
 * it attempts to retrieve the executable path using the PATH variable.
 * It returns the command path if accessible or NULL if an error occurs.
 *
 * @param cmd: A pointer to the command structure containing environment
 *             variables.
 * @param node: A pointer to the node containing the command token.
 * @param env_array: An array of environment variables used during execution.
 *
 * @return char*: The path of the executable or NULL if an error occurs.
 */

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

/**
 * @brief run_execve - Executes a command using execve.
 *
 * This function prepares the execution of a command by setting up the
 * environment and argument arrays. It forks a new process, redirects
 * the input/output if needed, and calls execve to run the command.
 * The function cleans up allocated memory after execution.
 *
 * @param command: A pointer to the command structure containing necessary
 *                 information for execution.
 * @param list: A pointer to the linked list of command nodes to be executed.
 *
 * @return void: This function does not return a value.
 */

void	run_execve(t_command *command, t_node *list)
{
	t_node	*node;
	char	*path;
	char	**env_array;
	char	**args;

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
