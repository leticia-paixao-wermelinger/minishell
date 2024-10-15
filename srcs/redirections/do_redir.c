/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 00:13:51 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/10/14 23:47:00 by lraggio          ###   ########.fr       */
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

*/

int	do_heredoc(t_node *sentence, t_tokens *redir_node, t_command *command)
{
	int	fds[2];
	int	child_pid;
	int	status;

	status = 0;
	pipe(fds);
	child_pid = fork();
	if (child_pid == 0)
		heredoc_child_process(fds, redir_node, command);
	if (child_pid > 1)
		waitpid(child_pid, &status, 0);
	close(fds[1]);
	if (sentence->fd_in != 0)
		close(sentence->fd_in);
	sentence->fd_in = fds[0];
	remove_redir_nodes(sentence, redir_node);
	if (!WIFEXITED(status))
		return (ERROR);
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

*/

int	do_append(t_node *sentence, t_tokens *redir_node)
{
	char	*filename;

	filename = redir_node->next->word;
	if (access(filename, F_OK) < 0)
	{
		if (sentence->fd_out != 1 && sentence->fd_out != 2)
			close(sentence->fd_out);
		sentence->fd_out = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	}
	else
	{
		if (check_permissions(filename, W_OK) == ERROR)
			return (ERROR);
		if (sentence->fd_out != 1 && sentence->fd_out != 2)
			close(sentence->fd_out);
		sentence->fd_out = open(filename, O_WRONLY | O_APPEND);
	}
	remove_redir_nodes(sentence, redir_node);
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

*/

int	do_redir_out(t_node *sentence, t_tokens *redir_node)
{
	char	*filename;

	filename = redir_node->next->word;
	if (access(filename, F_OK) < 0)
	{
		if (sentence->fd_out != 1 && sentence->fd_out != 2)
			close(sentence->fd_out);
		sentence->fd_out = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	}
	else
	{
		if (check_permissions(filename, W_OK) == ERROR)
			return (ERROR);
		if (sentence->fd_out != 1 && sentence->fd_out != 2)
			close(sentence->fd_out);
		sentence->fd_out = open(filename, O_WRONLY | O_TRUNC);
	}
	remove_redir_nodes(sentence, redir_node);
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
		remove_redir_nodes(sentence, redir_node);
		return (ERROR);
	}
	if (check_permissions(filename, R_OK) == ERROR)
		return (ERROR);
	if (sentence->fd_in != 0)
		close(sentence->fd_in);
	sentence->fd_in = open(filename, O_RDONLY);
	remove_redir_nodes(sentence, redir_node);
	return (NO_ERROR);
}
