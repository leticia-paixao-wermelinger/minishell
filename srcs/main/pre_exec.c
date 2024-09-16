/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:15:28 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/15 17:17:17 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pre_exec(t_command   *command)
{
	remove_all_quotes(command->l_input, DOUBLE_QUOT_MARK);
	var_exp(command);
	remove_all_quotes(command->l_input, SIMPLE_QUOT_MARK);
}
