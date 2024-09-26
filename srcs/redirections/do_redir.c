/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 00:13:51 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/26 09:18:25 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Redir Heredoc (<<):

The following function creates a temporary file, using pipe (opening 2 FDs, one
to write in the file and another to read from it.
In a loop, we wil call the readline and go saving its input to the FD that was
created with pipe.
If the delimiter (End of File - EOF) is sent as an input to readline,
the loop stops.
There is also a checking to limit the entrances to the size alloed by the fd.
In the end, it deletes the redirect and the delimiter
(EOF) from the linked list t_tokens.

TEM QUE TESTAR O SEU FUNCIONAMENTO DEPOIS COM A EXECUÇÃO TODA INTEGRADA
*/

// FALTA IMPLEMENTAR O STRL+C!

int	do_heredoc(t_node *sentence, t_tokens *redir_node, t_env *env)
{
	char	*delimiter;
	char	*str;
	int		written_to_pipe;
	int		fds[2];

	delimiter = redir_node->next->word;
	written_to_pipe = 0;
	str = NULL;
	pipe(fds);
	while (42)
	{
		str = readline("> ");
		if (!str)
			written_to_pipe += write(fds[0], "\n", 1);
		else if (my_strcmp(str, delimiter) == 0)
			break ;
		else
		{
			str = expand_heredoc_variables(str, env);
			written_to_pipe += write(fds[0], str, my_strlen(str));
			free(str);
			str = NULL;
		}
		if (written_to_pipe >= PIPE_BUF)
		{
			print_error("minishell: heredoc limit reached, the input will be truncated\n");
			break ;
		}
	}
	close(fds[0]);
	sentence->fd_in = fds[1];
	remove_word_token(redir_node->next, sentence->token);
	remove_word_token(redir_node, sentence->token);
	return (NO_ERROR);
}

/*
Redir Append (>>):

The following function checks if the file exists, using access.
If the file does not exists, we must create it.
If it does exists we, then, check if we have permission to write in it.
If we do, it then opens the file, saves the returned fd in the
struct sentence, for the executor to use it in dup2 afterwards.
The difference between the append (>>) and the output (>) is that
the append writes appendint to the end of the file, instead of replacing
what was in it before. For that, we use O_APPEND in the OPEN.
In the end, it deletes the redirect and the name
of the file from the linked list t_tokens.

TEM QUE TESTAR O SEU FUNCIONAMENTO DEPOIS COM A EXECUÇÃO TODA INTEGRADA
*/

int	do_append(t_node *sentence, t_tokens *redir_node)
{
	char	*filename;
	
	filename = redir_node->next->word;
	if (access(filename, F_OK) < 0)
		sentence->fd_out = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else
	{
		if (check_permissions(filename, W_OK) == ERROR)
			return (ERROR);
		sentence->fd_out = open(filename, O_WRONLY | O_APPEND);
	}
	remove_word_token(redir_node->next, sentence->token);
	remove_word_token(redir_node, sentence->token);
	return (NO_ERROR);
}

/*
Redir out (>):

The following function checks if the file exists, using access.
If the file does not exists, we must create it.
If it does exists we, then, check if we have permission to write in it.
If we do, it then opens the file, saves the returned fd in the
struct sentence, for the executor to use it in dup2 afterwards.
The difference between the output (>) and the append (>>) is that
the output redir writes from the beggining of the file, replacing the
previous content of the file. For that, we use O_TRUNC in the OPEN.
In the end, it deletes the redirect and the name
of the file from the linked list t_tokens.

TEM QUE TESTAR O SEU FUNCIONAMENTO DEPOIS COM A EXECUÇÃO TODA INTEGRADA
*/

int	do_redir_out(t_node *sentence, t_tokens *redir_node)
{
	char	*filename;

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
