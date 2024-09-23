/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:15:28 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/23 17:16:11 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pre_exec(t_command   *command)
{
	//pipe
	//fd
	if (find_heredoc(command->l_input))
		return (ERROR);
	remove_all_quotes(command->l_input, DOUBLE_QUOT_MARK);
	var_exp(command);
	remove_all_quotes(command->l_input, SIMPLE_QUOT_MARK);
	if (redirections(command->l_input))
		return (ERROR);
	return (NO_ERROR);
}
