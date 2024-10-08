/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:15:28 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/26 01:24:52 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * pre_exec - Prepares the command for execution by handling expansions.
 * 
 * This function removes quotes from the command input and performs variable
 * expansion. It processes both simple and double quotes. If any redirection
 * setup fails, the function returns an error code.
 *
 * @param command: A pointer to the `t_command` structure that holds the command 
 * input and associated data.
 */

int	pre_exec(t_command   *command)
{
//	printf("ENVIANDO A SEGUINTE LISTA PARA A PRÉ EXECUÇÃO:\n");
//	printlist(command->l_input);
	// ajustes de aspas simples múltiplas de 2 como: echo ''$PWD''
	single_quotes_to_unprintable(command->l_input);
	remove_all_quotes(command->l_input, SIMPLE_QUOT_MARK);
//	remove_all_quotes(command->l_input, DOUBLE_QUOT_MARK);
//	printf("APÓS REMOÇÃO DE ASPAS DUPLAS:\n");
//	printlist(command->l_input);
	var_exp(command);
	remove_all_quotes(command->l_input, DOUBLE_QUOT_MARK);
	remove_all_quotes(command->l_input, UNPRINT_CHAR);
//	printf("ANTES DE REMOVER NODES VAZIOS:\n");
//	printlist(command->l_input);
	remove_empty_nodes(command->l_input);
//	printf("ENVIANDO A SEGUINTE LISTA PARA A EXECUÇÃO:\n");
//	printlist(command->l_input);
	if (check_cmds(command->l_input) == ERROR)
		return (ERROR);
	return (NO_ERROR);
}
