/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:25:31 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/08/29 16:02:23 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern unsigned int   g_status;
/*
void	var_exp(t_command *command)
{
	t_node	*node;

	node = command->l_input;
	while (node)
	{
		search_dollar(node, node->value, command->my_env);
		node = node->next;
	}
}

void	search_dollar(t_node *list, char **str, t_env *env)
{
	int	i;
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
	}
}

int	check_post_dollar(t_node *list, char **str, int i, int j, t_env *env)
{
	int	index;

	index = 0;
	j++;
	(void)env;
	//printf("Em check_post_dollar: str[%i][%i] = |%c|\n", i, j, str[i][j]);
	if (str[i][j] == QUESTION_MARK)						// PRONTO
		index = print_global_var(list, str, i, j);
	else if (str[i][j] == DOLLAR)						// PRONTO
		index = double_dollar(list, str, i, j);
	else if ((int)my_strlen(str[i]) == j)				 // PRONTO
		return (j);
	else // substituir em value do input o nome da variável de ambiente pelo valor da mesma
	{
		index = 2;
		printf("Vai imprimir o valor da variável\n");
//		index = expand_variable(list, env, str, i, j);
	}
	return (index);
}*/
