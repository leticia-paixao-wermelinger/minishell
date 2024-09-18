/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:58:14 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/18 17:18:19 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void do_redir(t_tokens *token, enum e_token value);
static int  check_start(t_tokens *token);

void	search_tokens(t_node *input)
{
	t_node		*node;
	t_tokens	*token;
	int			beginning;
	int			count;

	node = input;
	beginning = 0;
	count = 0;
	while (node)
	{
		token = node->token;
		count = 0;
		beginning = check_start(token);
		while (token)
		{
			set_token(token, beginning, count);
			token = token->next;
			count++;
		}
		node = node->next;
	}
}

void	set_token(t_tokens *token, int command, int count)
{
	if (token->word == NULL)
		return ;
	if (token->type == REDIR_FILE)
		return ;
	else if (is_builtin(token->word) == TRUE)
		token->type = BUILTIN;
	else if (command == count)
		token->type = EXEC;
	else if (is_append(token->word) == TRUE)
		do_redir(token, REDIR_APPEND);
	else if (is_redir_out(token->word) == TRUE)
		do_redir(token, REDIR_OUT);
	else if (is_redir_in(token->word) == TRUE)
		do_redir(token, REDIR_IN);
	else if (is_heredoc(token->word) == TRUE)
		do_redir(token, REDIR_HEREDOC);
	else
		token->type = ARGUMENT;
}

static void	do_redir(t_tokens *token, enum e_token value)
{
	token->type = value;
	token->next->type = REDIR_FILE;
}

static int	check_start(t_tokens *token)
{
	t_tokens	*node;
	int			count;

	node = token;
	count = 0;
	if (node->word == NULL)
		return (count);
	while (node)
	{
		if (is_redirect(node->word) == TRUE)
		{
			count += 2;
			node = node->next;
		}
		else
			return (count);
		node = node->next;
	}
	return (count);
}

int	is_builtin(char *s)
{
	if (my_strcmp(s, "echo") == 0)
		return (TRUE);
	else if (my_strcmp(s, "cd") == 0)
		return (TRUE);
	else if (my_strcmp(s, "pwd") == 0)
		return (TRUE);
	else if (my_strcmp(s, "export") == 0)
		return (TRUE);
	else if (my_strcmp(s, "unset") == 0)
		return (TRUE);
	else if (my_strcmp(s, "env") == 0)
		return (TRUE);
	else if (my_strcmp(s, "exit") == 0)
		return (TRUE);
	return (FALSE);
}
