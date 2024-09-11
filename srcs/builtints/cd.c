/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 13:52:16 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/11 18:04:16 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void go_home(t_env *env, char *old_pwd);
static void	change_pwd(char *new_value, t_env *env);
static void	change_old_pwd(char *new_value, t_env *env);

int	my_cd(t_tokens *node, t_env *env)
{
	char    cwd[1824];
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
		printf("bash: cd: %s: No such file or directory\n", node->word); // Não vai pro stdout então não precisa de fd
		free(old_pwd);
		return (ERROR);
	}
	change_pwd(getcwd(cwd, sizeof(cwd)), env);
	change_old_pwd(old_pwd, env);
	free(old_pwd);
	return (NO_ERROR);
}

static void	go_home(t_env *env, char *old_pwd)
{
	t_env	*home;

	home = my_getenv_by_list("HOME", env);
	chdir(home->value);
	change_pwd(home->value, env);
	change_old_pwd(old_pwd, env);
}

static void	change_pwd(char *new_value, t_env *env)
{
	t_env	*node;
	
	node = my_getenv_by_list("PWD", env);
	free(node->value);
	node->value = my_strdup(new_value);
}

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
