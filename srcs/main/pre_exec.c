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

int	pre_exec(t_command   *command)
{
	remove_all_quotes(command->l_input, DOUBLE_QUOT_MARK);
	var_exp(command);
	remove_all_quotes(command->l_input, SIMPLE_QUOT_MARK);
	if (redirections(command->l_input, command->my_env))
		return (ERROR);
//	printf("ENVIANDO A SEGUINTE LISTA PARA A EXECUÇÃO:\n");
//	printlist(command->l_input);
	return (NO_ERROR);
}
