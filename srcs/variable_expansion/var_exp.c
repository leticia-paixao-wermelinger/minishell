/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:25:31 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/04 15:50:20 by lpaixao-         ###   ########.fr       */
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
	printf("Lista do input:\n");
	printlist(command->l_input);
}

void	search_dollar(t_node *list, t_tokens *node_token, t_env *env)
{
	t_tokens	*token;
	int			i;

	(void)list;
	token = node_token;
	while (token)
	{
		i = 0;
		while (token->word[i])
		{
			if (token->word[i] == DOLLAR)
				i = check_post_dollar(token, token->word, i, env);
			else
				i++;
		}
		token = token->next;
	}
}

int	check_post_dollar(t_tokens *token, char *str, int j, t_env *env)
{
	int	index;

	index = 0;
	j++;
	(void)env;
	printf("Em check_post_dollar: str[%i] = |%c|\n", j, str[j]);
	if (str[j] == QUESTION_MARK)						// PRONTO
	{
		printf("str[%i] == question_mark\n", j);
		index = print_global_var(token, str, j);
	}
	else if (str[j] == DOLLAR)							// PRONTO
	{
		printf("str[%i] == dollar\n", j);
		index = double_dollar(token, str, j);
	}
	else if ((int)my_strlen(str) == j)				 // PRONTO
		return (j);
	else // substituir em value do input o nome da variável de ambiente pelo valor da mesma
	{
//		j += 2;
		printf("Vai imprimir o valor da variável\n");
		index = expand_variable(token, env, str, j);
	}
	//index = j;
	return (index);
}
