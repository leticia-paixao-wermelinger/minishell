/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:25:31 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/25 14:32:50 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern unsigned int   g_status;

void	var_exp(t_command *command)
{
	t_node	*node;

	node = command->l_input;
	while (node)
	{
		search_dollar(node->token, command->my_env);
		node = node->next;
	}
}

void	search_dollar(t_tokens *node_token, t_env *env)
{
	t_tokens	*token;
	int			i;

	token = node_token;
	while (token)
	{
		i = 0;
		if (token->word == NULL || token->type == HEREDOC_EOF)
		{
			token = token->next;
			continue ;
		}
		while (token->word[i])
		{
			if (token->word[i] == DOLLAR)
			{
				if (dollar_is_closed_by_single_quote(&(token->word)) == TRUE)
					i++;
				else
					check_post_dollar(token, token->word, i, env);
			}
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
