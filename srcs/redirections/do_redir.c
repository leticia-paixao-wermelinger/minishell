/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 00:13:51 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/10/03 21:41:08 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	heredoc_loop(int *fds, t_tokens *redir_node, t_env *env, int count);

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

int	do_heredoc(t_node *sentence, t_tokens *redir_node, t_command *command)
{
	int			fds[2];
	int			child_pid;
	int			status;
	t_tokens	*temp;

	temp = NULL;
//	printf("Entrou na do_heredoc com redir_node->word = %s e redir_node->next->word = %s\n", redir_node->word, redir_node->next->word);
//	printf("Na do_heredoc, sentence->token->word = %s\n", sentence->token->word);
	status = 0;
	pipe(fds);
	child_pid = fork();
	if (child_pid == 0)
	{
		close(fds[0]);
		setup_heredoc_signal_handling();
		heredoc_loop(fds, redir_node, command->my_env, command->input_count);
		close(fds[1]);
		close_all_node_fds(command->l_input);
		clear_loop_end(command);
		final_clear(command);
		exit(g_status(-1));
	}
	if (child_pid > 1)
		waitpid(child_pid, &status, 0);
	close(fds[1]);
	if (sentence->fd_in != 0)
		close(sentence->fd_in);
	sentence->fd_in = fds[0];
//	printf("Em do_redir_out, vai apagar: |%s| &%p e |%s| - &%p\n", redir_node->next->word, redir_node->next, redir_node->word, redir_node);
//	printf("Em do_redir_out, start == |%s| &%p\n", sentence->token->word, sentence->token);
	if (sentence->token == redir_node)
	{
//		printf("Está na condição de sentence->token == redir_node\n");
		temp = redir_node->next->next;
	}
	remove_word_token(redir_node->next, sentence->token, sentence);
	remove_word_token(redir_node, sentence->token, sentence);
	if (temp != NULL)
//	{
//		printf("Está na condição de temp != NULL\n");
		sentence->token = temp;
//	}
//	else
//	{
//		printf("Entrou no else de sentence->token = NULL\n");
//		sentence->token = NULL;
//	}
//	printf("No final de heredoc, vai retornar com a estrutura:\n");
//	printlist(command->l_input);
//	printf("Antes de retornar heredoc, start = |%s|\n", sentence->token->word);
	if (!WIFEXITED(status))
		return (ERROR);
	return (NO_ERROR);
}

static void	heredoc_loop(int *fds, t_tokens *redir_node, t_env *env, int count)
{
	char	*delimiter;
	char	*str;
	int		written_to_pipe;
	int		size;

	delimiter = redir_node->next->word;
	written_to_pipe = 0;
	str = NULL;
	g_status(0);
	while (42)
	{
		str = readline("> ");
		if (g_status(-1) == 130)
		{
			free(str);
			str = NULL;
			break ;
		}
		if (!str)
		{
			print_heredoc_ctrld(count, delimiter);
			break ;
		}
		else if (my_strcmp(str, delimiter) == 0)
		{
			free(str);
			str = NULL;
			break ;
		}
		else
		{
			if (only_spaces(str) != ERROR)
				str = expand_heredoc_variables(str, env);
			size = my_strlen(str);
			written_to_pipe += write(fds[1], str, size);
			written_to_pipe += write(fds[1], "\n", 1);

		}
		free(str);
		str = NULL;
		if (written_to_pipe >= PIPE_BUF)
		{
			print_error("minishell: heredoc limit reached, the input will be truncated\n");
			break ;
		}
	}
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

	t_tokens    *temp;

	temp = NULL;
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
	if (sentence->token == redir_node)
		temp = redir_node->next->next;
	remove_word_token(redir_node->next, sentence->token, sentence);
	remove_word_token(redir_node, sentence->token, sentence);
	if (temp != NULL)
		sentence->token = temp;
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
	char		*filename;
	t_tokens	*temp;

	temp = NULL;
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
	if (sentence->token == redir_node)
		temp = redir_node->next->next;
	remove_word_token(redir_node->next, sentence->token, sentence);
	remove_word_token(redir_node, sentence->token, sentence);
	if (temp != NULL)
		sentence->token = temp;
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
	t_tokens    *temp;

	temp = NULL;
	filename = redir_node->next->word;
	if (access(filename, F_OK) < 0)
	{
		no_such_file(filename);
		return (ERROR);
	}
	if (check_permissions(filename, R_OK) == ERROR)
		return (ERROR);
	if (sentence->fd_in != 0)
			close(sentence->fd_in);
	sentence->fd_in = open(filename, O_RDONLY);
	if (sentence->token == redir_node)
		temp = redir_node->next->next;
	remove_word_token(redir_node->next, sentence->token, sentence);
	remove_word_token(redir_node, sentence->token, sentence);
	if (temp != NULL)
		sentence->token = temp;
	return (NO_ERROR);
}
