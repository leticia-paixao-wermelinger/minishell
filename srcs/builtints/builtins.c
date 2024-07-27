/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 22:13:01 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/07/27 11:51:57 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	run_builtin(t_command *command, t_node *node)
{
	if (my_strncmp(node->value, "echo", 4) == 0)
		printf("Chamar função echo\n");
	else if (my_strncmp(node->value, "cd", 2) == 0)
		printf("Chamar função cd\n");
	else if (my_strcmp(node->value, "pwd") == 0)
		return (pwd(command));
	else if (my_strcmp(node->value, "export") == 0)
		printf("Chamar função export\n");
	else if (my_strcmp(node->value, "unset") == 0)
		printf("Chamar função unset\n");
	else if (my_strcmp(node->value, "env") == 0)
		print_env(command->my_env);
	else if (my_strcmp(node->value, "exit") == 0)
		return (CLOSE);
	return (NO_ERROR);
}

int	pwd(t_command *command)
{
	char	*path;
	path = my_getenv_by_list("PWD", command->my_env);
	if (!path)
		return (ERROR);
	printf("%s\n", path);
	return (NO_ERROR);
}
