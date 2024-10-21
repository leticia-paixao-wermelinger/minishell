
#include "../../includes/minishell.h"

/**
 * @brief is_redir_out
- Checks if the given string is a redirection output operator.
 *
 * This function checks whether the provided string is the output redirection
 * operator (`>`). It is useful in parsing commands to identify output
 * redirection.
 *
 * @param s: The string to be checked.
 *
 * @return int: Returns TRUE if the string is `>`, otherwise returns FALSE.
 */

int	is_redir_out(char *s)
{
	if (my_strcmp(s, ">") == 0)
		return (TRUE);
	return (FALSE);
}

/**
 * @brief is_redir_in
- Checks if the given string is a redirection input operator.
 *
 * This function checks whether the provided string is the input redirection
 * operator (`<`). It helps in parsing commands to detect input redirection.
 *
 * @param s: The string to be checked.
 *
 * @return int: Returns TRUE if the string is `<`, otherwise returns FALSE.
 */

int	is_redir_in(char *s)
{
	if (my_strcmp(s, "<") == 0)
		return (TRUE);
	return (FALSE);
}

/**
 * @brief is_heredoc - Checks if the given string is a heredoc operator.
 *
 * This function checks whether the provided string is the heredoc redirection
 * operator (`<<`). It is essential for parsing commands that involve heredoc
 * functionality in the minishell.
 *
 * @param s: The string to be checked.
 *
 * @return int: Returns TRUE if the string is `<<`, otherwise returns FALSE.
 */

int	is_heredoc(char *s)
{
	if (my_strcmp(s, "<<") == 0)
		return (TRUE);
	return (FALSE);
}

/**
 * @brief is_redirect
- Checks if the given string is any type of redirection operator.
 *
 * This function checks if the provided string is a valid redirection operator,
 * which includes output (`>`), input (`<`), heredoc (`<<`), and append (`>>`).
 * It is useful for comprehensive command parsing in the minishell.
 *
 * @param str: The string to be checked.
 *
 * @return int: Returns TRUE if the string is one of the redirection operators,
 *              otherwise returns FALSE.
 */

int	is_redirect(char *str)
{
	if (my_strcmp(str, ">>") == 0 || my_strcmp(str, "<<") == 0)
		return (TRUE);
	else if (my_strcmp(str, ">") == 0 || my_strcmp(str, "<") == 0)
		return (TRUE);
	return (FALSE);
}

/**
 * @brief token_is_redir
- Checks if the token represents a redirection operation.
 *
 * This function verifies whether the provided token is of a type associated
 * with redirection operations, including output redirection, input redirection,
 * heredoc, and append redirection. This is critical in evaluating command
 * tokens in the minishell context.
 *
 * @param node: The token node to be checked.
 *
 * @return int: Returns TRUE if the token type is one of the redirection types,
 *              otherwise returns FALSE.
 */

int	token_is_redir(t_tokens *node)
{
	if (node->type == REDIR_APPEND || node->type == REDIR_HEREDOC)
		return (TRUE);
	else if (node->type == REDIR_OUT || node->type == REDIR_IN)
		return (TRUE);
	return (FALSE);
}
