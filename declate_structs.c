/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declate_structs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:32:50 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/06/20 15:35:55 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_command(t_command *command)
{
	command->prompt = make_prompt();
	command->input = readline(command->prompt);
}
