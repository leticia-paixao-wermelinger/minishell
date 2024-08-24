/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:25:31 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/08/23 19:12:28 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern unsigned int   g_status;

void	var_exp(t_command *command)
{
	t_node	*node;

	node = l_input;
	while (node)
	{
		search_dollar(command, command->value);
		node = node->next;
	}
}

void	search_dollar(t_command *command, char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i][j])
		{
			if (str[i][j] == DOLLAR)
				j += check_post_dollar(command, str, i, j);
			else
				j++;
		}
		i++;
	}
}

int	check_post_dollar(t_command *command, char **str, int i, int j)
{
	int	count;

	count = 1;
	j++;
	if (str[i][j] == QUESTION_MARK)
		// substituir em value o $? pela variável global g_status
	else if (str[i][j] == DOLLAR)
		// substituir em value o $$ por apenas 1 $
	else
	{
		// substituir o nome da variável de ambiente pelo valor da mesma
	}
}
