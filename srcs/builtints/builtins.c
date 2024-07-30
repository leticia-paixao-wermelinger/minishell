/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 22:13:01 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/07/29 21:03:26 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	pre_export(char **str, t_command *command, t_node *node);
static void	pre_unset(char **str, t_command *command, t_node *node);

int	run_builtin(t_command *command, t_node *node)
{
	char	*str;

	str = NULL;
	if (my_strncmp(node->value, "echo", 4) == 0)
		printf("Chamar função echo\n");
	else if (my_strncmp(node->value, "cd", 2) == 0)
		printf("Chamar função cd\n");
	else if (my_strcmp(node->value, "pwd") == 0)
		return (pwd(command));
	else if (my_strncmp(node->value, "export", 6) == 0)
		pre_export(&str, command, node);
	else if (my_strncmp(node->value, "unset", 5) == 0)
		pre_unset(&str, command, node);
	else if (my_strcmp(node->value, "env") == 0)
		print_env(command->my_env);
	else if (my_strcmp(node->value, "exit") == 0)
		return (CLOSE);
	if (str)
		free(str);
	return (NO_ERROR);
}

static void	pre_export(char **str, t_command *command, t_node *node)
{
	if (strlen(node->value) > 6)
		*str = fromstrcdup(node->value, SPACE_CHAR);
//	printf("TESTE: str = |%s|\n", str);
	my_export(*str, command);
}

static void	pre_unset(char **str, t_command *command, t_node *node)
{
	if (strlen(node->value) > 6)
		*str = fromstrcdup(node->value, SPACE_CHAR);
	my_unset(*str, command);
}
