/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:43:21 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/20 16:50:57 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_error(char *str)
{
	my_putstr_fd(str, 2);
}

int	print_pipe_syntax_error(int	flag)
{
	if (flag == 1)
		print_error("bash: syntax error near unexpected token `|'\n");
	else if (flag == 2)
		print_error("bash: syntax error near unexpected token `||'\n");
	return (ERROR);
}
