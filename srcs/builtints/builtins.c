/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 22:13:01 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/07/30 23:14:47 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	pre_export(t_command *command, t_node *node);
static void	pre_unset(t_command *command, t_node *node);

int	run_builtin(t_command *command, t_node *node)
{
	int		ret;

	ret = NO_ERROR;
	if (my_strncmp(node->value, "echo", 4) == 0)
		printf("Chamar função echo\n");
	else if (my_strncmp(node->value, "cd", 2) == 0)
		printf("Chamar função cd\n");
	else if (my_strcmp(node->value, "pwd") == 0)
		ret = pwd(command);
	else if (my_strncmp(node->value, "export", 6) == 0)
		ret = pre_export(command, node);
	else if (my_strncmp(node->value, "unset", 5) == 0)
		pre_unset(command, node);
	else if (my_strcmp(node->value, "env") == 0)
		print_env(command->my_env);
	else if (my_strcmp(node->value, "exit") == 0) // Se der tempo, colocar parâmetros
		ret = CLOSE;
	return (ret);
}

static int	pre_export(t_command *command, t_node *node)
{
	char    *str;
	int	ret;

	str = NULL;
	ret = NO_ERROR;
	if (my_strlen(node->value) > 6)
//	{
//		printf("Entrou no if de 'strlen'\n");
		str = fromstrcdup(node->value, SPACE_CHAR);
//		printf("Passou da fromstrcdup e ficou com str = %s", str);
//	}
//	printf("Vai verificar se str existe c str = %s\n", str);
	if (str)
	{
//		printf("Entrou no if de 'str' e vai passar a check_export_error. str = %s\n", str);
		ret = check_export_error(&str);
//		printf("Passou pela check_export_error c ret = %d\n", ret);
	}
//	my_printf("Vai verificar se não tem erro em ret c ret = %d e c str = %s\n", ret, str);
	if (ret == NO_ERROR)
	{
//		printf("Entrou no if de 'NO_ERROR' e vai chamar a my_export c str = %s\n", str);
		my_export(&str, command);
//		printf("Passou pela my_export c str = %s\n", str);
	}
	free(str);
	return (ret);
}

static void	pre_unset(t_command *command, t_node *node)
{
	char    *str;

	str = NULL;
	if (my_strlen(node->value) > 6)
		str = fromstrcdup(node->value, SPACE_CHAR);
	my_unset(str, command);
	free(str);
}
