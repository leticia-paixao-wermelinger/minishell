
#include "../../includes/minishell.h"

/**
 * @brief tokenize_sentence - Tokenizes an input string into an array of
 *                            substrings based on spaces, respecting quotes.
 *
 * This function processes the input string and replaces occurrences of
 * spaces with a special unprintable character, allowing the string to be
 * split into an array of substrings. It respects quoted sections, meaning
 * that spaces within quotes are ignored.
 *
 * @param input A pointer to the input string that needs to be tokenized.
 *
 * @return Returns an array of strings (char**) containing the tokenized
 *         substrings, or NULL if an error occurs during processing.
 *
 * @note The caller is responsible for freeing the returned array and
 *       the individual strings it contains. The function assumes that
 *       the input string is properly formatted and does not contain
 *       unbalanced quotes.
 */

char	**tokenize_sentence(char *input)
{
	int	quote_state;
	int	i;

	quote_state = 0;
	i = 0;
	while (input[i])
	{
		if (is_simple_quote(input[i]) && (quote_state == 0 || quote_state == 1))
			quote_state ^= 1;
		else if (is_double_quote(input[i]) && (quote_state == 0
				|| quote_state == 2))
			quote_state ^= 2;
		else if (input[i] == SPACE_CHAR && quote_state == 0)
			input[i] = UNPRINT_CHAR;
		i++;
	}
	return (my_split(input, UNPRINT_CHAR));
}
