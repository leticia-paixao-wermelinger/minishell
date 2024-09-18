/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:15:28 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/18 17:18:19 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pre_exec(t_command   *command)
{
	remove_all_quotes(command->l_input, DOUBLE_QUOT_MARK);
	var_exp(command);
	remove_all_quotes(command->l_input, SIMPLE_QUOT_MARK);
}
