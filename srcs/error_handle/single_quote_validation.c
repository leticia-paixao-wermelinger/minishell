
#include "../../includes/minishell.h"

static void	change_single_quotes(char *str, \
		enum e_flag double_quote, enum e_flag simple_quote);
static int	multiple_of_2_quotes(char *str);
static void	count_quotes(char *str, int *counter, \
		enum e_flag *double_quote, enum e_flag *simple_quote);

/**
 * single_quotes_to_unprintable - Converts single quotes to unprintable chars.
 *
 * This function converts single quotes within a token's word to unprintable
 * characters if there is an uneven number of quotes.
 *
 * @param list: The linked list of nodes to process.
 *
 * @return void: This function does not return a value.
 */

void	single_quotes_to_unprintable(t_node *list)
{
	t_node		*temp;
	t_tokens	*words;

	temp = list;
	while (temp)
	{
		words = temp->token;
		while (words)
		{
			if (multiple_of_2_quotes(words->word) == FALSE)
				change_single_quotes(words->word, OFF, OFF);
			words = words->next;
		}
		temp = temp->next;
	}
}

/**
 * change_single_quotes - Replaces single quotes with unprintable characters.
 *
 * This function traverses the string `str` and replaces single quotes with
 * an unprintable character if they are not properly enclosed.
 *
 * @param str: The input string to process.
 *
 * @return void: This function does not return a value.
 */

static void	change_single_quotes(char *str, \
		enum e_flag double_quote, enum e_flag simple_quote)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i] == DOUBLE_QUOT_MARK && double_quote == OFF \
			&& simple_quote == OFF)
			double_quote = ON;
		else if (str[i] == SIMPLE_QUOT_MARK && simple_quote == OFF \
			&& double_quote == OFF)
		{
			str[i] = UNPRINT_CHAR;
			simple_quote = ON;
		}
		else if (str[i] == DOUBLE_QUOT_MARK && double_quote == ON)
			double_quote = OFF;
		else if (str[i] == SIMPLE_QUOT_MARK && simple_quote == ON)
		{
			str[i] = UNPRINT_CHAR;
			simple_quote = OFF;
		}
		i++;
	}
}

/**
 * multiple_of_2_quotes - Checks if the string has an even number of quotes.
 *
 * This function checks if the string `str` contains an even number of single
 * quotes, indicating that they are properly enclosed.
 *
 * @param str: The input string to check.
 *
 * @return TRUE if the string contains an even number of single quotes.
 *         FALSE if there is an uneven number of single quotes.
 */

static int	multiple_of_2_quotes(char *str)
{
	int			counter;
	enum e_flag	double_quote;
	enum e_flag	simple_quote;

	counter = 0;
	double_quote = OFF;
	simple_quote = OFF;
	count_quotes(str, &counter, &double_quote, &simple_quote);
	if (counter > 3 && counter % 2 == 0)
		return (TRUE);
	return (FALSE);
}

static void	count_quotes(char *str, int *counter, \
		enum e_flag *double_quote, enum e_flag *simple_quote)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == DOUBLE_QUOT_MARK && *double_quote == OFF \
				&& *simple_quote == OFF)
			*double_quote = ON;
		else if (str[i] == DOUBLE_QUOT_MARK && *double_quote == ON)
			*double_quote = OFF;
		else if (str[i] == SIMPLE_QUOT_MARK && *simple_quote == OFF \
				&& *double_quote == OFF)
		{
			(*counter)++;
			*simple_quote = ON;
		}
		else if (str[i] == SIMPLE_QUOT_MARK && *simple_quote == ON)
		{
			(*counter)++;
			*simple_quote = OFF;
		}
		i++;
	}
}
