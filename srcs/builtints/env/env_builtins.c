/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:18:34 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/10/14 18:52:18 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	process_export(t_env *env, t_tokens *temp);

/**
 * print_env - Prints all environment variables.
 *
 * This function prints each environment variable as key-value pairs in the
 * format "key=value" followed by a newline.
 *
 * @param list: A linked list of environment variables.
 * @param fd: The file descriptor to which the output will be written.
 *
 * @return void: This function does not return a value.
 */

void	print_env(t_env *list, int fd)
{
	t_env	*temp;

	temp = list;
	while (temp)
	{
		my_putstr_fd(temp->key, fd);
		my_putstr_fd("=", fd);
		my_putstr_fd(temp->value, fd);
		my_putstr_fd("\n", fd);
		temp = temp->next;
	}
}

/**
 * my_export - Handles the 'export' command to set environment variables.
 *
 * This function sets or updates environment variables based on the tokens
 * passed. If no tokens are provided, it prints all environment variables
 * in a format suitable for 'export'. For each valid token, the function
 * either updates an existing environment variable or creates a new one.
 *
 * @param env: A linked list of environment variables.
 * @param node_t: A linked list of tokens representing the variables to be
 *                exported.
 * @param fd: The file descriptor to which the output will be written if no
 *            tokens are provided.
 *
 * @return void: This function does not return a value.
 */

void	my_export(t_env *env, t_tokens *node_t, int fd)
{
	t_tokens	*temp;

	temp = node_t;
	if (node_t == NULL)
		print_env_for_export(env, fd);
	while (temp)
	{
		if (is_valid_ev(temp->word) == ERROR)
		{
			temp = temp->next;
			continue ;
		}
		else
			process_export(env, temp);
		temp = temp->next;
	}
}

static void	process_export(t_env *env, t_tokens *temp)
{
	char	*str;
	t_env	*node_env;

	str = fromstrcdup(temp->word, '=');
	node_env = my_getenv_by_list(temp->word, env);
	if (node_env != NULL)
		change_env_value(node_env, str);
	else
		create_new_ev(temp->word, env);
	free(str);
}

/**
 * my_unset - Handles the 'unset' command to remove environment variables.
 *
 * This function removes environment variables from the list based on the
 * tokens passed. For each valid token, the corresponding environment
 * variable is removed.
 *
 * @param env: A linked list of environment variables.
 * @param node_i: A linked list of tokens representing the variables to
 *                be unset.
 *
 * @return void: This function does not return a value.
 */

void	my_unset(t_env *env, t_tokens *node_i)
{
	t_env		*node_env;
	t_tokens	*temp;

	temp = node_i;
	node_env = NULL;
	while (temp)
	{
		if (!temp->word)
		{
			temp = temp->next;
			continue ;
		}
		node_env = my_getenv_by_list(temp->word, env);
		if (node_env != NULL)
			remove_env(node_env, env);
		temp = temp->next;
	}
}
