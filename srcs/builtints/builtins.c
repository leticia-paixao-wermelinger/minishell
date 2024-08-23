/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 22:13:01 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/08/22 22:42:33 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//static int	pre_export(t_command *command, t_node *node);

int	run_builtin(t_command *command, t_node *node, int fd)
{
	int		ret;

	ret = NO_ERROR;
	if (my_strcmp(node->value[0], "echo") == 0)
		my_echo(node, fd);
	else if (my_strcmp(node->value[0], "cd") == 0)
		ret = my_cd(node, command->my_env);
	else if (my_strcmp(node->value[0], "pwd") == 0)
		ret = pwd(command);
	else if (my_strcmp(node->value[0], "export") == 0)
		my_export(command->my_env, node, fd);
	else if (my_strcmp(node->value[0], "unset") == 0)
		my_unset(command->my_env, node);
	else if (my_strcmp(node->value[0], "env") == 0)
		print_env(command->my_env, fd);
	else if (my_strcmp(node->value[0], "exit") == 0) // Se der tempo, colocar parâmetros
		ret = CLOSE;
	return (ret);
}
/*
static int	pre_export(t_command *command, t_node *node)
{
	char    *str;
	int	ret;

	str = NULL;
	ret = NO_ERROR;
	(void)command;
	(void)node;
	printf("Entrou na pre_export\n");
	
	if (my_strlen(*node->value) > 6)
//	{
//		printf("Entrou no if de 'strlen'\n");
		str = fromstrcdup(*node->value, SPACE_CHAR);
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
}*/
