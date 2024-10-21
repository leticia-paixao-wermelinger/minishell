
#include "../../includes/minishell.h"

static void	do_redir(t_tokens *token, enum e_token value);
static int	check_start(t_tokens *token);

/**
 * @brief search_tokens - Assigns types to tokens in a linked list
 *                       of input nodes based on their position and
 *                       value.
 *
 * This function traverses through each node in the input linked list,
 * processes the tokens, and assigns types to each token. The type
 * of each token is determined by its position in the command
 * sequence and its value. The function also considers leading
 * redirection tokens.
 *
 * @param input A pointer to the head of the linked list of input nodes.
 *               Each node contains a list of tokens to be processed.
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
 * @brief set_token - Sets the type of a given token based on its value
 *                    and position in the command sequence.
 *
 * This function checks the token's word and assigns a type such as
 * BUILTIN, EXEC, REDIR, or ARGUMENT. The function also handles
 * redirection tokens and determines if they are valid based on their
 * next token.
 *
 * @param token A pointer to the token whose type is to be set.
 * @param command The position of the command in the sequence.
 * @param count The index of the current token being processed.
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
 * @brief do_redir - Sets the type of a token for redirection and
 *                   propagates redirection types to subsequent tokens.
 *
 * This function assigns a type to a token and recursively checks the
 * next token to assign the appropriate redirection type based on its value.
 *
 * @param token A pointer to the token being processed for redirection.
 * @param value The type of redirection to assign.
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
 * @brief check_start - Checks the initial tokens in a sequence
 *                      to determine how many leading redirection
 *                      tokens are present.
 *
 * This function counts leading redirection tokens in a list of tokens
 * and returns the count. If the first token is not a redirection,
 * it returns the current count.
 *
 * @param token A pointer to the first token in the sequence.
 * @return The number of leading redirection tokens.
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
 * @brief is_builtin - Checks if the given string is a built-in command.
 *
 * This function compares the input string with known built-in commands
 * and returns TRUE if it matches any of them, otherwise returns FALSE.
 *
 * @param s A pointer to the string to be checked.
 * @return Returns TRUE if the string is a built-in command, otherwise FALSE.
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
