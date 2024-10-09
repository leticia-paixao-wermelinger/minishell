/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:22:22 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/09 16:30:18 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_cmds(t_node *sentence)
{
	while (sentence->token == NULL) //pro caso $nao_existo
	{
		if (sentence->next)
			sentence = sentence->next;
		else
			return (ERROR);
	}
	if (is_there_space(sentence->token->word))
		print_errno(sentence);
	return (NO_ERROR);
}

int	is_valid_cmd(t_node *sentence)
{
	while (sentence->token == NULL)
	{
		if (sentence->next)
		{
			close_all_node_fds(sentence);
			sentence = sentence->next;
		}
		else
			return (close_all_node_fds(sentence), FALSE);
	}
	return (NO_ERROR);
}
