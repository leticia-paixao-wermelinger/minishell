
#include "../../includes/minishell.h"

/**
 * @brief is_char - Checks if two characters are equal.
 *
 * This function compares two characters to determine if they are the same.
 * It is a simple utility function that can be used in various contexts
 * within the minishell, such as checking for specific characters
 * during command parsing or handling user input.
 *
 * @param o: The first character to be compared.
 * @param c: The second character to be compared.
 *
 * @return int: Returns TRUE if the characters are equal, otherwise
 *              returns FALSE.
 */

int	is_char(char o, char c)
{
	if (o == c)
		return (TRUE);
	return (FALSE);
}
