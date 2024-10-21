
#include "../../includes/minishell.h"

static int	handle_dollar(t_tokens *token, int i, t_env *env);

/**
 * @brief Expands variables for all tokens in a command.
 *
 * This function iterates through the linked list of tokens in the provided
 * command structure (`t_command`) and calls `search_dollar` for each token.
 * This is crucial for expanding environment variables and special tokens
 * like "$?" and "$$" during command execution in the minishell.
 *
 * @param command The command structure containing the list of tokens
 *                to process for variable expansion.
 */

void	var_exp(t_command *command)
{
	t_node	*node;

	node = command->l_input;
	while (node)
	{
		search_dollar(node->token, command->my_env);
		node = node->next;
	}
}

/**
 * @brief Searches for dollar signs in a token list and expands them.
 *
 * This function traverses a list of tokens, looking for dollar signs
 * that indicate variable expansion. It handles cases where the dollar
 * sign is closed by quotes or followed by specific characters like
 * "?" or "$". The function modifies tokens in place to reflect the
 * expanded values, enabling dynamic command construction in the minishell.
 *
 * @param node_token The first token in the linked list to search for
 *                   dollar signs and expand variables.
 * @param env The linked list of environment variables used for expansion.
 */

void	search_dollar(t_tokens *node_token, t_env *env)
{
	t_tokens	*token;
	int			i;

	token = node_token;
	while (token)
	{
		i = 0;
		if (token->word == NULL || token->type == HEREDOC_EOF)
		{
			token = token->next;
			continue ;
		}
		while (token->word[i])
		{
			if (token->word[i] == DOLLAR)
				i = handle_dollar(token, i, env);
			else
				i++;
		}
		token = token->next;
	}
}

static int	handle_dollar(t_tokens *token, int i, t_env *env)
{
	if (dollar_is_closed_by_quote(&(token->word), i, UNPRINT_CHAR) == TRUE)
		i++;
	else
	{
		if (check_post_dollar(token, token->word, i, env) == CLOSE)
			i++;
	}
	return (i);
}

/**
 * @brief Checks and expands variables following a dollar sign in a token.
 *
 * This function analyzes the character following a dollar sign in a token
 * to determine the appropriate expansion action. It handles special cases
 * for "$?" (exit status) and "$$" (process ID) and calls the relevant
 * expansion functions. The index of the next character to process is
 * returned, enabling continuous processing of the token's string.
 *
 * @param token The token containing the dollar sign to expand.
 * @param str The string of the token that may contain variables.
 * @param j The index of the dollar sign within the token's string.
 * @param env The linked list of environment variables used for expansion.
 * @return The updated index after processing the dollar sign, or
 *         CLOSE if no further expansion is needed.
 */

int	check_post_dollar(t_tokens *token, char *str, int j, t_env *env)
{
	int	index;

	index = 0;
	j++;
	if (str[j] == QUESTION_MARK)
		index = print_global_var(token, str, j);
	else if (str[j] == DOLLAR)
		index = double_dollar(token, str, j);
	else if ((int)my_strlen(str) == j)
		return (CLOSE);
	else
	{
		expand_variable(token, env, str, j);
		index = j - 2;
	}
	return (index);
}
