
#include "../../includes/minishell.h"

/**
 * pipe_syntax_error - Reports a syntax error related to pipes.
 *
 * This function prints an error message indicating a syntax error
 * near an unexpected pipe token. It differentiates between a single
 * pipe (`|`) and a double pipe (`||`) based on the provided flag.
 *
 * @param flag: An integer flag indicating the type of syntax error.
 *              - 1: Single pipe syntax error
 *              - 2: Double pipe syntax error
 *
 * @return int: Returns ERROR to indicate that the error has occurred.
 */

int	pipe_syntax_error(int flag)
{
	if (flag == 1)
		print_error("minishell: syntax error near unexpected token `|'\n");
	else if (flag == 2)
		print_error("minishell: syntax error near unexpected token `||'\n");
	g_status(MISUSE);
	return (ERROR);
}

/**
 * redir_syntax_error - Reports a syntax error related to redirection.
 *
 * This function prints an error message indicating a syntax error
 * near an unexpected redirection token. The type of redirection is
 * specified by the provided enum token.
 *
 * @param e: An enumerator representing the type of redirection error.
 *            Possible values include:
 *            - REDIR_IN: Input redirection (`<`)
 *            - REDIR_OUT: Output redirection (`>`)
 *            - REDIR_APPEND: Append redirection (`>>`)
 *            - REDIR_HEREDOC: Here-document redirection (`<<`)
 *
 * @return int: Returns ERROR to indicate that the error has occurred.
 */

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
	g_status(MISUSE);
	return (ERROR);
}
