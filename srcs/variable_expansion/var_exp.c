/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:25:31 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/10 15:18:38 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern unsigned int   g_status;

/*
VALIDAR ASPAS SIMPLES: NÃO PODE EXPANDIR
*/

void	var_exp(t_command *command)
{
	t_node	*node;

	node = command->l_input;
	while (node)
	{
		search_dollar(node->token, command->my_env);
		node = node->next;
	}
	printf("Lista do input:\n");
	printlist(command->l_input);
}

void	search_dollar(t_tokens *node_token, t_env *env)
{
	t_tokens	*token;
	int			i;

	token = node_token;
	while (token)
	{
		i = 0;
		while (token->word[i])
		{
			if (token->word[i] == DOLLAR)
				check_post_dollar(token, token->word, i, env);
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
	if (str[j] == QUESTION_MARK)
	{
		printf("str[%i] == question_mark\n", j);
		index = print_global_var(token, str, j);
	}
	else if (str[j] == DOLLAR)
	{
		printf("str[%i] == dollar\n", j);
		index = double_dollar(token, str, j);
	}
	else if ((int)my_strlen(str) == j)
		return (j);
	else
	{
		expand_variable(token, env, str, j);
		index = j - 2;
	}
	return (index);
}
