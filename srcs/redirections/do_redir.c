/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 00:13:51 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/24 15:57:50 by lpaixao-         ###   ########.fr       */
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

/*
Redir out (>):

CHECAR TUDO, O Q É IGUAL E O Q NÃO É!


The following function checks if the file exists, using access.
If the file does not exists, we must create it.
If it does exists we, then, check if we have permission to write in it.
If we do, it then opens the file, saves the returned fd in the
struct sentence, for the executor to use it in dup2 afterwards.
In the end, it deletes the redirect and the name
of the file from the linked list t_tokens.
*/

int	do_redir_out(t_node *sentence, t_tokens *redir_node)
{
	char	*filename;

	printf("Vai fazer redir_out com %s\n", redir_node->word);
	filename = redir_node->next->word;
	if (access(filename, F_OK) < 0)
		sentence->fd_out = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else
	{
		if (check_permissions(filename, W_OK) == ERROR)
			return (ERROR);
		sentence->fd_out = open(filename, O_WRONLY | O_TRUNC);
	}
	remove_word_token(redir_node->next, sentence->token);
	remove_word_token(redir_node, sentence->token);
	return (NO_ERROR);
}

/*
Redir in (<):

The following function checks if the file exists, using access.
If it does, it, then, checks if we have permission to read it.
If we do, it then opens the file, saves the returned fd in the
struct sentence, for the executor to use it in dup2 afterwards.
In the end, it deletes the redirect and the name
of the file from the linked list t_tokens.
*/

int	do_redir_in(t_node *sentence, t_tokens *redir_node)
{
	char	*filename;

	filename = redir_node->next->word;
	if (access(filename, F_OK) < 0)
	{
		no_such_file(filename);
		return (ERROR);
	}
	if (check_permissions(filename, R_OK) == ERROR)
		return (ERROR);
	sentence->fd_in = open(filename, O_RDONLY);
	remove_word_token(redir_node->next, sentence->token);
	remove_word_token(redir_node, sentence->token);
	return (NO_ERROR);
}
