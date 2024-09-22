/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:43:21 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/21 22:48:13 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern volatile unsigned int    g_status;

void	print_error(char *str)
{
	my_putstr_fd(str, 2);
}

int	pipe_syntax_error(int flag)
{
	if (flag == 1)
		print_error("minishell: syntax error near unexpected token `|'\n");
	else if (flag == 2)
		print_error("minishell: syntax error near unexpected token `||'\n");
	g_status = MISUSE;
	return (ERROR);
}

int	redir_syntax_error(enum e_token e)
{
	print_error("minishell: syntax error near unexpected token `");
	if (e == REDIR_IN)
		print_error("<");
	if (e == REDIR_OUT)
		print_error(">");
	if (e == REDIR_APPEND)
		print_error(">>");
	if (e == REDIR_HEREDOC)
		print_error("<<");
	print_error("'\n");
	g_status = MISUSE;
	return (ERROR);
}
