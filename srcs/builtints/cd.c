/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 13:52:16 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/10/14 17:52:32 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	go_home(t_env *env, char *old_pwd);
static void	change_pwd(char *new_value, t_env *env);
static void	change_old_pwd(char *new_value, t_env *env);

/**
 * my_cd - Implements the behavior of the 'cd' built-in command.
 *
 * This function changes the current working directory. If no argument is 
 * provided, it changes the directory to the user's home directory. If an 
 * argument is provided, it tries to change the directory to the path 
 * specified by the token. If the directory doesn't exist, it prints an 
 * error message.
 *
 * After changing the directory, it updates the environment variables PWD 
 * and OLDPWD to reflect the new current and previous working directories.
 *
 * @param node: A linked list of tokens, where the first token is the target 
 *              directory.
 * @param env: The environment linked list, used to update PWD and OLDPWD.
 *
 * @return int: Returns `NO_ERROR` on success; otherwise, returns `ERROR` if 
 * the directory does not exist.
 */

int	my_cd(t_tokens *node, t_env *env)
{
	char	cwd[1824];
	char	*old_pwd;
	int		ret;

	old_pwd = my_strdup((my_getenv_by_list("PWD", env))->value);
	if (!node)
	{
		go_home(env, old_pwd);
		free(old_pwd);
		return (NO_ERROR);
	}
	ret = chdir(node->word);
	if (ret != 0)
	{
		printf("bash: cd: %s: No such file or directory\n", node->word);
		free(old_pwd);
		return (ERROR);
	}
	change_pwd(getcwd(cwd, sizeof(cwd)), env);
	change_old_pwd(old_pwd, env);
	free(old_pwd);
	return (NO_ERROR);
}

/**
 * go_home - Changes the working directory to the user's home directory.
 *
 * This function retrieves the HOME environment variable and changes the 
 * working directory to the value of HOME. If HOME is not set, it prints an 
 * error message. After changing the directory, it updates PWD and OLDPWD.
 *
 * @param env: The environment linked list, used to find HOME and update 
 *             PWD/OLDPWD.
 * @param old_pwd: The previous working directory to be set as OLDPWD.
 *
 * @return void: This function does not return a value.
 */

static void	go_home(t_env *env, char *old_pwd)
{
	t_env	*home;

	home = my_getenv_by_list("HOME", env);
	if (!home)
	{
		printf("bash: cd: HOME not set\n");
		return ;
	}
	chdir(home->value);
	change_pwd(home->value, env);
	change_old_pwd(old_pwd, env);
}

/**
 * change_pwd - Updates the PWD environment variable.
 *
 * This function updates the PWD environment variable to reflect the new 
 * working directory after a successful directory change.
 *
 * @param new_value: The new current working directory to be set as PWD.
 * @param env: The environment linked list, where the PWD variable is updated.
 *
 * @return void: This function does not return a value.
 */

static void	change_pwd(char *new_value, t_env *env)
{
	t_env	*node;

	node = my_getenv_by_list("PWD", env);
	free(node->value);
	node->value = my_strdup(new_value);
}

/**
 * change_old_pwd - Updates the OLDPWD environment variable.
 *
 * This function updates the OLDPWD environment variable to reflect the 
 * previous working directory. If OLDPWD doesn't exist in the environment, 
 * it creates a new node for it.
 *
 * @param new_value: The previous working directory to be set as OLDPWD.
 * @param env: The environment linked list, where the OLDPWD variable is 
 *             updated or created.
 *
 * @return void: This function does not return a value.
 */

static void	change_old_pwd(char *new_value, t_env *env)
{
	t_env	*node;
	t_env	*temp;
	char	*old_pwd;
	char	*str;

	temp = env;
	old_pwd = my_strdup("OLDPWD=");
	str = NULL;
	node = my_getenv_by_list("OLDPWD", env);
	if (!node)
	{
		while (temp->next != NULL)
			temp = temp->next;
		str = my_strjoin(old_pwd, new_value);
		create_last_env_node(str, temp);
		free(str);
	}
	else
	{
		free(node->value);
		node->value = my_strdup(new_value);
	}
	free(old_pwd);
}
