/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 22:13:01 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/11 18:31:10 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//static int	pre_export(t_command *command, t_node *node);

int	run_builtin(t_tokens *token, t_env *env, int fd)
{
	int			ret;

	ret = NO_ERROR;
	if (my_strcmp(token->word, "echo") == 0) // AJUSTADO
		my_echo(token->next, fd);
	else if (my_strcmp(token->word, "cd") == 0)
		ret = my_cd(token->next, env);
	else if (my_strcmp(token->word, "pwd") == 0) // AJUSTADO
		ret = pwd();
	else if (my_strcmp(token->word, "export") == 0)
		printf("Falta ajustar export\n");
		//my_export(env, token->next, fd);
	else if (my_strcmp(token->word, "unset") == 0)
		//printf("Falta ajustar unset\n");
		my_unset(env, token->next);
	else if (my_strcmp(token->word, "env") == 0)
		print_env(env, fd);
	else if (my_strcmp(token->word, "exit") == 0) // Se der tempo, colocar parâmetros
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
