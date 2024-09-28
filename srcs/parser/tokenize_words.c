/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:58:14 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/25 14:22:09 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	do_redir(t_tokens *token, enum e_token value);
static int 	check_start(t_tokens *token);

/**
 * search_tokens - Processes tokens in each node and assigns types to them.
 * 
 * This function iterates through a linked list of nodes (`t_node`), and for each node,
 * it processes its token list (`t_tokens`). It checks if the first token in each node 
 * represents the start of a command and then sets the token types based on the 
 * content of each token. The token type could be a built-in command, an executable, 
 * an argument, or a redirection operator.
 *
 * @param input: A pointer to the head of the linked list of input nodes (`t_node`), where 
 * each node contains a list of tokens.
 */

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

/**
 * set_token - Assigns a type to a token based on its content and position.
 * 
 * This function checks the content of a token and assigns an appropriate type to it. 
 * The type could be a built-in command, an executable, a file redirection, or an argument. 
 * It processes redirection tokens such as append, input, output, and heredoc, ensuring 
 * that the next token in the sequence is treated as a redirection target (e.g., a file).
 *
 * @param token: A pointer to the current token (`t_tokens`) that is being processed.
 * @param command: An integer representing the position of the command token in the list.
 * @param count: The current index of the token in the token list for the current command.
 */

void	set_token(t_tokens *token, int command, int count)
{
	if (token->word == NULL)
		return ;
	if (token->type == REDIR_FILE || token->type == HEREDOC_EOF)
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

/**
 * do_redir - Sets the token type for a redirection operation.
 * 
 * This static helper function is used to assign the correct type to tokens that represent 
 * redirection operators (e.g., `>`, `>>`, `<`, `<<`). It recursively processes subsequent 
 * tokens to determine if they are part of the redirection sequence and marks them 
 * appropriately. For heredoc operations, the end-of-file token is also marked.
 *
 * @param token: A pointer to the current token (`t_tokens`) being processed.
 * @param value: An enumeration value (`e_token`) that represents the type of redirection 
 *               (e.g., `REDIR_APPEND`, `REDIR_OUT`, `REDIR_IN`, etc.).
 */

static void	do_redir(t_tokens *token, enum e_token value)
{
	token->type = value;
	if (is_append(token->next->word) == TRUE)
		do_redir(token->next, REDIR_APPEND);
	else if (is_redir_out(token->next->word) == TRUE)
		do_redir(token->next, REDIR_OUT);
	else if (is_redir_in(token->next->word) == TRUE)
		do_redir(token->next, REDIR_IN);
	else if (is_heredoc(token->next->word) == TRUE)
		do_redir(token->next, REDIR_HEREDOC);
	else if (is_heredoc(token->word) == TRUE)
		token->next->type = HEREDOC_EOF;
	else
		token->next->type = REDIR_FILE;
}

/**
 * check_start - Determines if the first token is a redirection and calculates an offset.
 * 
 * This function checks the beginning of a token list to determine if the first tokens 
 * are redirection operators (e.g., `>`, `>>`, `<`). It counts the number of redirection 
 * tokens and skips them, returning an offset indicating how many tokens to skip 
 * before reaching the actual command token.
 *
 * @param token: A pointer to the first token (`t_tokens`) in the list.
 *
 * @return int: The number of tokens to skip if redirection is found, or 0 if no 
 * redirection is present at the start.
 */

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

/**
 * is_builtin - Checks if a string corresponds to a built-in shell command.
 * 
 * This function compares a given string to a set of known built-in shell commands 
 * (e.g., `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`). If the string matches 
 * one of these commands, it returns `TRUE`. Otherwise, it returns `FALSE`.
 *
 * @param s: The string to be checked.
 *
 * @return int: Returns `TRUE` if the string is a built-in command, `FALSE` otherwise.
 */

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
