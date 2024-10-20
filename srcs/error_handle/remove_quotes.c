
#include "../../includes/minishell.h"

static void	remove_quote_2(char *temp, char **str);
static int	quote_is_valid(char *str, int j, int quote);
static void	remove_quotes_from_word(char **word, int quote);

/**
 * remove_all_quotes
 * @brief Removes all quotes from the tokens in a node list.
 *
 * This function iterates over a list of nodes, and for each node, it checks all
 * tokens for quotes. If a quote is found, it calls `remove_quote()`
 * to delete it.
 * The process repeats for all tokens and nodes in the list.
 *
 * @param list A pointer to the list of nodes to process.
 * @param quote The ASCII value of the quote to be removed (either single
 * or double).
 */

void	remove_all_quotes(t_node *list, int quote)
{
	t_node		*node;
	t_tokens	*token;

	node = list;
	while (node)
	{
		token = node->token;
		while (token)
		{
			if (token->word == NULL)
			{
				token = token->next;
				continue ;
			}
			remove_quotes_from_word(&(token->word), quote);
			token = token->next;
		}
		node = node->next;
	}
}

static void	remove_quotes_from_word(char **word, int quote)
{
	int	i;

	i = 0;
	while (i <= (int)my_strlen(*word) && (*word)[i])
	{
		if ((*word)[i] == quote && quote_is_valid(*word, i, quote) == TRUE)
			remove_quote(word, i, quote);
		else
			i++;
	}
}

/**
 * quote_is_valid
 * @brief Checks if a quote is valid at a specific position in the string.
 *
 * This function verifies if a quote at position `j` in the string is valid for
 * removal. It does this by checking if there is a matching opening or closing
 * quote of the opposite type (single or double) earlier in the string.
 *
 * @param str The string to check.
 * @param j The index of the quote to validate.
 * @param quote The ASCII value of the quote being checked.
 *
 * @return TRUE if the quote is valid for removal, FALSE otherwise.
 */

static int	quote_is_valid(char *str, int j, int quote)
{
	int			i;
	int			sec_quote;
	enum e_flag	sec_flag;

	i = 0;
	sec_flag = OFF;
	if (quote == DOUBLE_QUOT_MARK)
		sec_quote = UNPRINT_CHAR;
	else if (quote == UNPRINT_CHAR || quote == SIMPLE_QUOT_MARK)
		sec_quote = DOUBLE_QUOT_MARK;
	while (str[i] && i < j)
	{
		if (str[i] == sec_quote && sec_flag == OFF)
			sec_flag = ON;
		else if (str[i] == sec_quote && sec_flag == ON)
			sec_flag = OFF;
		i++;
	}
	if (sec_flag == ON)
		return (FALSE);
	return (TRUE);
}

/**
 * remove_quote - Removes a valid quote from the word at the given position `i`.
 * @brief Removes a quote character at a specific position in the string.
 *
 * This function removes a quote character (either single or double) at position
 * `i` in the string by creating new substrings that omit the quote and then
 * joining the substrings back together.
 *
 * @param str A pointer to the string from which the quote will be removed.
 * @param i The index of the quote in the string.
 * @param quote The ASCII value of the quote to remove.
 */

void	remove_quote(char **str, int i, enum e_ascii quote)
{
	char	*first;
	char	*temp;
	char	*seccond;

	first = NULL;
	temp = fromstrldup(*str, i);
	seccond = my_strcdup(temp, quote);
	free(temp);
	if (i != 0)
	{
		first = my_strldup(*str, i);
		temp = my_strjoin(first, seccond);
	}
	else
		temp = my_strdup(seccond);
	free(first);
	free(seccond);
	remove_quote_2(temp, str);
}

/**
 * remove_quote_2 - Helper function to finalize the removal of a quote.
 * @brief Helper function to complete the quote removal process.
 *
 * This function finalizes the removal of a quote by joining the modified string
 * segments back together, ensuring the final result is properly formed.
 *
 * @param temp The temporary string with part of the quote removed.
 * @param str A pointer to the original string being modified.
 */

static void	remove_quote_2(char *temp, char **str)
{
	int		j;
	char	*last;

	last = NULL;
	j = my_strlen(temp);
	if ((*str)[j + 2] != '\0')
	{
		last = fromstrldup(*str, j + 1);
		free(*str);
		*str = NULL;
		*str = my_strjoin(temp, last);
	}
	else
	{
		free(*str);
		*str = NULL;
		*str = my_strdup(temp);
	}
	free(temp);
	free(last);
}
