/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:06:43 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/15 18:40:45 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * @brief pipe_execution - Forks a new process to execute a command
 *                        in a piped context.
 *
 * This function creates a child process to execute a command. If the
 * command is a built-in, it calls `run_pipe_builtin`, otherwise it
 * calls `run_pipe_execve`. The function handles the duplication of
 * file descriptors for input and output redirection, ensuring that
 * commands can communicate through pipes. The exit status of the child
 * process is set and passed back to the parent process.
 *
 * @param command: A pointer to the `t_command` structure containing
 *                 command information and environment variables.
 * @param node: A pointer to the `t_node` representing the command to be
 *              executed.
 *
 * @return int: Returns NO_ERROR on success, or the exit status of the
 *              executed command if an error occurs.
 */

void	check_next_node(t_node *node)
{
	if (node->next != NULL && node->next->token == NULL)
		do_dup2(node);
	else
	{
		if (node->fd_in != STDIN_FILENO)
			dup2(node->fd_in, STDIN_FILENO);
		if (node->fd_out != STDOUT_FILENO)
			dup2(node->fd_out, STDOUT_FILENO);
	}
}

int	pipe_execution(t_command *command, t_node *node)
{
	int	ret;

	ret = NO_ERROR;
	node->pid = fork();
	if (node->pid == 0)
	{
		if (node->token->type != BUILTIN)
			run_pipe_execve(command, node);
		else
		{
			check_next_node(node);
			/*if (node->fd_in != STDIN_FILENO)
			dup2(node->fd_in, STDIN_FILENO);
			if (node->fd_out != STDOUT_FILENO)
			dup2(node->fd_out, STDOUT_FILENO);*/
			ret = run_pipe_builtin(command, node->token, command->my_env,
					node->fd_out);
			close_all_node_fds(node);
		}
		ret = node->exit_status;
		clear_loop_end(command);
		final_clear(command);
		exit(ret);
	}
	return (ret);
}

/**
 * @brief run_pipe_execve - Executes a command using execve in a piped context.
 *
 * This function handles the execution of a command in a piped environment
 * by preparing the necessary arguments and environment variables. It
 * checks the command's path using `check_path`, then constructs an
 * argument array with `cmd_list_to_array` and duplicates file descriptors
 * as necessary. The function attempts to execute the command using
 * `execve`. In case of errors, it cleans up any allocated resources.
 *
 * @param command: A pointer to the `t_command` structure containing
 *                 command information and environment variables.
 * @param list: A pointer to the head of the linked list of `t_node`
 *              structures representing the commands to be executed.
 *
 * @return void: This function does not return a value.
 *
 * @note The function ensures proper cleanup of resources in case of
 *       failure. If the command is not found or executable, it handles
 *       the error gracefully.
 */

void	run_pipe_execve(t_command *command, t_node *list)
{
	t_node	*node;
	t_node	*temp;
	char	*path;
	char	**env_array;
	char	**args;

	node = list;
	env_array = envp_list_to_array(command->my_env);
	path = check_path(command, node, env_array);
	if (!path)
		return (close_all_node_fds(node), free_matrix(env_array));
	args = cmd_list_to_array(node);
	do_dup2(node);
	temp = node;
	close_all_node_fds(temp);
	execve(path, args, env_array);
	if (path != node->token->word)
		free(path);
	execve_clean(args, env_array);
	return ;
}

/**
 * @brief run_pipe_builtin - Executes built-in commands within a pipe.
 *
 * This function checks the type of the command represented by the
 * `t_tokens` structure and executes the corresponding built-in command
 * function (such as `echo`, `cd`, `pwd`, etc.). It uses the file
 * descriptor `fd` for output redirection if necessary. This is
 * important for handling built-in commands separately from external
 * commands in the minishell.
 *
 * @param command: A pointer to the `t_command` structure containing
 *                 command information and environment variables.
 * @param token: A pointer to the `t_tokens` structure representing the
 *               command token to be executed.
 * @param env: A pointer to the environment list used by the built-in
 *             commands.
 * @param fd: The file descriptor for output redirection.
 *
 * @return int: Returns the exit status of the executed built-in command
 *              or zero if no built-in command was executed.
 */

int	run_pipe_builtin(t_command *command, t_tokens *token, t_env *env, int fd)
{
	int	ret;

	ret = 0;
	if (my_strcmp(token->word, "echo") == 0)
		ret = my_echo(token->next, fd);
	else if (my_strcmp(token->word, "cd") == 0)
		ret = my_cd(token->next, env);
	else if (my_strcmp(token->word, "pwd") == 0)
		ret = pwd();
	else if (my_strcmp(token->word, "export") == 0)
		my_export(env, token->next, fd);
	else if (my_strcmp(token->word, "unset") == 0)
		my_unset(env, token->next);
	else if (my_strcmp(token->word, "env") == 0)
		print_env(env, fd);
	else if (my_strcmp(token->word, "exit") == 0)
		ret = my_exit(token->next, command);
	return (ret);
}

/**
 * @brief check_path
	- Verifies if a command's executable and retrieves its path.
 *
 * This function checks if the command specified in the given `t_node`
 * structure is accessible and executable. If the command is not found
 * or not executable, it attempts to retrieve its executable path from
 * the environment. If the command has permission issues, it prints an
 * error message and cleans up allocated resources. This is critical for
 * the minishell to ensure that commands are valid before execution.
 *
 * @param cmd: A pointer to the `t_command` structure containing command
 *             information and environment variables.
 * @param node: A pointer to the `t_node` representing the command to be
 *              executed.
 * @param env_array: An array of strings representing the environment
 *                   variables, used to search for executable paths.
 *
 * @return char*: Returns the executable path of the command if it exists
 *                and is accessible, or NULL if an error occurred or
 */

char	*check_path(t_command *cmd, t_node *node, char **env_array)
{
	if (access(node->token->word, (F_OK | X_OK)) != 0)
	{
		if (errno == EACCES)
		{
			do_dup2(node);
			close_node_fds(node);
			print_errno(node);
			free_matrix(env_array);
			return (free_matrix(env_array), NULL);
		}
		return (get_executable_path(cmd, node));
	}
	else
		return (node->token->word);
}
