
#include "../../includes/minishell.h"

/**
 * @brief parser - Parses the input command and generates a list of tokens.
 *
 * This function performs validation on the user's input command,
 * splits the command by the pipe character ('|'), and generates
 * a linked list of commands. It also searches for tokens and
 * performs additional validation on the tokens created.
 *
 * @param command A pointer to a t_command structure that contains
 *                the user input and necessary data for parsing.
 *
 * @return Returns NO_ERROR (0) on successful parsing,
 *         or ERROR (-1) if any validation fails or if parsing
 *         cannot be completed.
 *
 * @note If the input command is invalid, the function clears the
 *       command input and associated resources before returning.
 */

int	parser(t_command *command)
{
	if (first_input_validation(command) == ERROR)
	{
		clear_input(command);
		return (ERROR);
	}
	command->input_matrix = split_sentence_by_char(command->input, '|');
	make_list_from_input(command);
	my_clean_vect(command->input_matrix);
	command->input_matrix = NULL;
	search_tokens(command->l_input);
	if (general_input_validation(command->l_input) == ERROR)
	{
		clear_loop_end(command);
		return (ERROR);
	}
	return (NO_ERROR);
}

/**
 * @brief split_sentence_by_char - Splits a string by a specified character
 *                                  while respecting quotes.
 *
 * This function processes the input string and replaces occurrences of a
 * specified character (usually a delimiter) with a special unprintable
 * character, allowing for the splitting of the string into an array
 * of substrings. It respects quoted sections, meaning that delimiters
 * within quotes are ignored.
 *
 * @param input A pointer to the input string that needs to be split.
 * @param c The character by which the string will be split.
 *
 * @return Returns an array of strings (char**) containing the split
 *         substrings, or NULL if an error occurs during processing.
 *
 * @note The caller is responsible for freeing the returned array and
 *       the individual strings it contains. The function assumes that
 *       the input string is properly formatted and does not contain
 *       unbalanced quotes.
 */

char	**split_sentence_by_char(char *input, char c)
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
		else if (is_char(input[i], c) && quote_state == 0)
			input[i] = UNPRINT_CHAR;
		i++;
	}
	return (my_split(input, UNPRINT_CHAR));
}
