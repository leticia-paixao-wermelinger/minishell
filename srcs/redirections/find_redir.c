
#include "../../includes/minishell.h"

static int	check_redir(t_node *temp, t_tokens *word, t_command *command,
				int first_flag);
static int	handle_redirections_first(t_node *temp, t_tokens **word,
				t_command *command, int *flag_first);
static int	handle_redirections_second(t_node *temp, t_tokens **word,
				t_command *command, int flag_first);

/**
 * @brief redirections - Handles redirections for a linked list of commands.
 *
 * This function iterates through the linked list of commands and processes
 * redirection tokens for each command. It checks for various types of
 * redirections and applies them accordingly.
 *
 * @param sentence A pointer to the linked list of commands (`t_node`)
 *                 to process for redirection.
 * @param command A pointer to the command structure that may be needed
 *                during redirection.
 * @return An integer indicating the status of the redirection:
 *         - NO_ERROR if successful,
 *         - ERROR if a problem occurred during redirection.
 */

int	redirections(t_node *sentence, t_command *command, int ret, int flag_first)
{
	t_node		*temp;
	t_tokens	*word;

	temp = sentence;
	while (temp)
	{
		word = temp->token;
		flag_first = ON;
		while (word)
		{
			if (flag_first == ON)
				ret = handle_redirections_first(temp, &word, command,
						&flag_first);
			if (!(sentence->token))
				return (sentence->token = NULL, ret);
			if (word != NULL)
				ret = handle_redirections_second(temp, &word, command,
						flag_first);
			if (ret == ERROR)
				return (ERROR);
		}
		temp = temp->next;
	}
	return (ret);
}

static int	handle_redirections_first(t_node *temp, t_tokens **word,
		t_command *command, int *flag_first)
{
	t_tokens	*temp_token;
	int			ret;

	while (*word && token_is_redir(*word) == TRUE)
	{
		temp_token = *word;
		ret = check_redir(temp, temp_token, command, *flag_first);
		if (temp->token != NULL)
			*word = temp->token;
		else
			*word = NULL;
		if (ret == ERROR)
			temp->exit_status = 1;
	}
	*flag_first = OFF;
	return (ret);
}

static int	handle_redirections_second(t_node *temp, t_tokens **word,
		t_command *command, int flag_first)
{
	int	ret;

	ret = NO_ERROR;
	if ((*word)->next != NULL)
	{
		ret = check_redir(temp, *word, command, flag_first);
		if (ret == -1)
			*word = (*word)->next;
	}
	else
		*word = (*word)->next;
	return (ret);
}

/**
 * @brief check_redir - Checks and executes the appropriate redirection
 *                      for a given token.
 *
 * This function determines the type of redirection based on the token's type
 * and applies the corresponding redirection function. It can handle appending,
 * output redirection, input redirection, and here-document redirection.
 *
 * @param sentence A pointer to the command node (`t_node`)
 *                 containing the redirection.
 * @param word A pointer to the token (`t_tokens`) representing the
 *             redirection operation.
 * @param command A pointer to the command structure that may be needed
 *                during redirection.
 * @param first_flag An integer flag indicating if this is the first
 *                   redirection check (for handling special cases).
 * @return An integer indicating the status of the redirection:
 *         - -1 if no valid redirection was found,
 *         - 0 if successful,
 *         - 1 if an error occurred.
 */

static int	check_redir(t_node *sentence, t_tokens *word, t_command *command,
		int first_flag)
{
	int			ret;
	t_tokens	*node_token;

	ret = -1;
	if (first_flag != ON)
		node_token = word->next;
	else
		node_token = word;
	if (node_token->type == REDIR_APPEND)
		ret = do_append(sentence, node_token);
	else if (node_token->type == REDIR_OUT)
		ret = do_redir_out(sentence, node_token);
	else if (node_token->type == REDIR_IN)
		ret = do_redir_in(sentence, node_token);
	else if (node_token->type == REDIR_HEREDOC)
		ret = do_heredoc(sentence, node_token, command);
	return (ret);
}
