/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 00:13:51 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/24 12:02:49 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	do_heredoc(t_node *sentence, t_tokens *word)
{
	(void)sentence;
	(void)word;
	printf("Vai fazer heredoc com %s\n", word->word);
	return (NO_ERROR);
}

int	do_append(t_node *sentence, t_tokens *word)
{
	(void)sentence;
	(void)word;
	printf("Vai fazer append com %s\n", word->word);
	return (NO_ERROR);
}

int	do_redir_out(t_node *sentence, t_tokens *word)
{
	(void)sentence;
	(void)word;
	printf("Vai fazer redir_out com %s\n", word->word);
	return (NO_ERROR);
}

/*
Redir in (<):

Verificar se existe: lstat

Se sim, ver se tem permissão: access

Abrir e salvar o fd de retorno do open, o dup2
*/

int	do_redir_in(t_node *sentence, t_tokens *word)
{
//	int	fd;

//	fd = sentence->fd_in;
	(void)sentence;
	if (access(word->word, F_OK) < 0)
	{
		no_such_file(word->word);
		return (ERROR);
	}
	if (check_permissions(word->word, R_OK) == ERROR)
	{
		return (ERROR);
	}
	// Se funcionar:
	//fd = open();
	//dup2();
	return (NO_ERROR);
}
