/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:27:09 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/15 20:11:40 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

extern volatile unsigned int	g_flag;

/**
 * @brief executor - Executes a list of commands in a minishell.
 *
 * This function orchestrates the execution of commands by checking
 * for errors, handling pipes, managing redirections, validating
 * commands, executing them, and updating the process status.
 *
 * @param command: A pointer to the command structure containing
 *                 the execution context.
 * @param sentence: A pointer to the linked list of command nodes
 *                  to be executed.
 *
 * @return int: Returns NO_ERROR if commands are executed
 *              successfully or ERROR if any issue arises.
 */

int	executor(t_command *command, t_node *sentence)
{
	t_node	*current_node;
	int		has_pipe;

	if (check_cmds(sentence) == ERROR)
		return (ERROR);
	has_pipe = has_pipe_or_not(sentence);
	if (has_pipe == TRUE)
		make_pipe(sentence);
	if (redirections(sentence, command, NO_ERROR, ON) == ERROR)
		return (close_all_node_fds(sentence), ERROR);
	is_valid_cmd(sentence);
	execute_cmds(command, sentence, has_pipe);
	current_node = sentence;
	wait_cmds(current_node);
	update_status(current_node);
	return (NO_ERROR);
}

/**
 * @brief execute_cmds - Executes individual commands in a node list.
 *
 * This function iterates through a linked list of command nodes
 * and executes them based on whether piping is required. It handles
 * the closing of file descriptors after each command execution.
 *
 * @param command: A pointer to the command structure containing
 *                 the execution context.
 * @param sentence: A pointer to the linked list of command nodes.
 * @param has_pipe: An integer flag indicating if piping is used.
 *
 * @return void: This function does not return a value.
 */

void	execute_cmds(t_command *command, t_node *sentence, int has_pipe)
{
	t_node	*current_node;

	current_node = sentence;
	while (current_node)
	{
		if (current_node->token != NULL)
		{
			if (!has_pipe)
				run_simple_commands(command, current_node);
			else
				pipe_execution(command, current_node);
		}
		close_node_fds(current_node);
		current_node = current_node->next;
	}
	current_node = sentence;
	close_all_node_fds(current_node);
}

/**
 * @brief run_simple_commands - Executes a single command node.
 *
 * This function checks the type of the command in the node and
 * executes it either as a builtin or a regular executable,
 * delegating the work to the appropriate functions.
 *
 * @param command: A pointer to the command structure containing
 *                 the execution context.
 * @param node: A pointer to the command node to be executed.
 *
 * @return void: This function does not return a value.
 */

void	run_simple_commands(t_command *command, t_node *node)
{
	t_node	*current_node;

	current_node = node;
	if (current_node->token->type == BUILTIN)
		run_builtin(command, current_node, command->my_env, node->fd_out);
	else
		run_execve(command, current_node);
}

/**
 * @brief wait_cmds - Waits for all child processes to finish.
 *
 * This function iterates through the command nodes and waits for
 * each child process to complete, collecting their exit status.
 *
 * @param node: A pointer to the linked list of command nodes
 *              that are being executed.
 *
 * @return void: This function does not return a value.
 */

void	wait_cmds(t_node *node)
{
	t_node	*current_node;

	current_node = node;
	while (current_node)
	{
		if (current_node->pid != 0)
			waitpid(current_node->pid, &current_node->exit_status, 0);
		current_node = current_node->next;
	}
}

/**
 * @brief update_status - Updates the global status based on
 *                       command exit statuses.
 *
 * This function checks the exit status of each command in the
 * linked list and updates the global status variable accordingly.
 * It handles special cases for signals and error codes.
 *
 * @param sentence: A pointer to the linked list of command nodes
 *                  whose statuses are to be updated.
 *
 * @return void: This function does not return a value.
 */

void	update_status(t_node *sentence)
{
	t_node	*node;

	node = sentence;
	if (g_status(-1) == 130 && g_flag == 130)
	{
		g_flag = 0;
		return ;
	}
	while (node)
	{
		if (node->exit_status != 0)
		{
			if (node->exit_status >= 255)
				g_status(WEXITSTATUS(node->exit_status));
			else
				g_status(node->exit_status);
		}
		else
			g_status(NO_ERROR);
		node = node->next;
	}
}
