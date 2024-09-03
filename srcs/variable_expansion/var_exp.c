/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:25:31 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/03 19:23:18 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern unsigned int   g_status;

void	var_exp(t_command *command)
{
	t_node	*node;

	node = command->l_input;
	while (node)
	{
		search_dollar(node, node->token, command->my_env);
		node = node->next;
	}
}

void	search_dollar(t_node *list, t_tokens *node_token, t_env *env)
{
	t_tokens	*token;
	int			i;

	token = node_token;
	i = 0;
	while (token)
	{
		while (token->word[i])
		{
			if (token->word[i] == DOLLAR)
				i = check_post_dollar(list, token->word, i, env);
			else
				i++;
		}
		token = token->next;
	}
/*	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			printf("Antes do if_else: str[%i][%i] = %c\n", i, j, str[i][j]);
			if (str[i][j] == DOLLAR)
			{
				j = check_post_dollar(list, str, i, j, env);
//				printf("Depois da check_post_dollar, dentro do if: str[%i][%i] = %c\n", i, j, str[i][j]);
			}
			else
				j++;
		}
		i++;
	}*/
}

int	check_post_dollar(t_node *list, char *str, int j, t_env *env)
{
	int	index;

	index = 0;
	j++;
	(void)list;
	(void)env;
	//printf("Em check_post_dollar: str[%i][%i] = |%c|\n", i, j, str[i][j]);
	if (str[j] == QUESTION_MARK)						// PRONTO
	//	printf("str[%i] == question_mark\n", j);
		index = print_global_var(list, str, j);
	else if (str[j] == DOLLAR)							// PRONTO
		printf("str[%i] == dollar\n", j);
	//	index = double_dollar(list, str, j);
/*	else if ((int)my_strlen(str[i]) == j)				 // PRONTO
		return (j);*/
	else // substituir em value do input o nome da variável de ambiente pelo valor da mesma
	{
		index = 2;
		printf("Vai imprimir o valor da variável\n");
//		index = expand_variable(list, env, str, i, j);
	}
	index = j;
	return (index);
}
