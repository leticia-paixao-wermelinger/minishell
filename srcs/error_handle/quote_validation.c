
#include "../../includes/minishell.h"

/**
 * n_quote_validation - Validates the closure of quotes in a string.
 *
 * This function traverses the string `str` and checks if all single ('') and
 * double quotes ("") are properly closed. If there is a missing closing quote,
 * it prints a syntax error, sets the global status to MISUSE, and returns
 * ERROR.
 *
 * @param str: The input string to be validated for proper quote closure.
 *
 * @return ERROR if quotes are not properly closed.
 *         NO_ERROR if all quotes are properly closed.
 */

int	n_quote_validation(char *str, enum e_flag double_quote, \
		enum e_flag simple_quote)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i] == DOUBLE_QUOT_MARK && double_quote == OFF
			&& simple_quote == OFF)
			double_quote = ON;
		else if (str[i] == SIMPLE_QUOT_MARK && simple_quote == OFF
			&& double_quote == OFF)
			simple_quote = ON;
		else if (str[i] == DOUBLE_QUOT_MARK && double_quote == ON)
			double_quote = OFF;
		else if (str[i] == SIMPLE_QUOT_MARK && simple_quote == ON)
			simple_quote = OFF;
		i++;
	}
	if (double_quote == ON || simple_quote == ON)
	{
		g_status(MISUSE);
		print_error("minishell: syntax error without quotes closure\n");
		return (ERROR);
	}
	return (NO_ERROR);
}

/**
 * dollar_is_closed_by_quote - Checks if a dollar sign is inside quotes.
 *
 * This function checks if a dollar sign ('$') in the string is enclosed by
 * quotes. If so, it determines whether the string contains a closing quote.
 *
 * @param str: The string to check.
 * @param quote: The type of quote to check for (single or double).
 *
 * @return TRUE if a dollar sign is enclosed by quotes.
 *         FALSE if there is no enclosing quote for the dollar sign.
 */

int	dollar_is_closed_by_quote(char **str, int index_dollar, int quote)
{
	int			i;
	int			quote_index;
	enum e_flag	quote_flag;

	i = 0;
	(void)quote_index;
	quote_flag = OFF;
	while ((*str)[i] && i <= index_dollar)
	{
		if ((*str)[i] == quote && quote_flag == OFF)
		{
			quote_index = i;
			quote_flag = ON;
		}
		else if ((*str)[index_dollar] == DOLLAR && quote_flag == ON)
			return (TRUE);
		i++;
	}
	return (FALSE);
}
