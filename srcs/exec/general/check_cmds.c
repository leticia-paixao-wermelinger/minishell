/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:22:22 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/15 20:07:16 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * @brief check_cmds - Validates the command nodes in a linked list.
 *
 * This function iterates through the linked list of command nodes and
 * checks if each node has an associated token. If a token is missing,
 * it moves to the next node. If it reaches the end of the list without
 * finding a valid token, it returns an error. If a token contains
 * spaces, it logs an error message.
 *
 * @param sentence: A pointer to the first node of the command list.
 *
 * @return int: Returns NO_ERROR if a valid command is found or ERROR
 *              if no valid command is present.
 */

int	check_cmds(t_node *sentence)
{
	while (sentence->token == NULL)
	{
		if (sentence->next)
			sentence = sentence->next;
		else
			return (ERROR);
	}
	if (is_there_space(sentence->token->word))
	{
		if (!sentence->next)
		{
			print_errno(sentence);
			return (ERROR);
		}
		else
			sentence = sentence->next;
	}
	return (NO_ERROR);
}

/**
 * @brief is_valid_cmd - Checks if a command node is valid.
 *
 * This function traverses the linked list of command nodes, checking
 * for the presence of tokens in each node. If a node lacks a token,
 * it closes all file descriptors associated with the nodes and returns
 * FALSE. If all nodes are valid, it returns NO_ERROR.
 *
 * @param sentence: A pointer to the first node of the command list.
 *
 * @return int: Returns NO_ERROR if the command is valid or FALSE if
 *              an invalid command is found.
 */

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
