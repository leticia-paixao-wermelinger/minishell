
#include "../../includes/minishell.h"

/**
 * is_there_space - Checks if a string contains a space character.
 *
 * This function iterates through the given string and returns TRUE if it
 * finds at least one space character. Otherwise, it returns FALSE.
 *
 * @param str: The string to be checked for space characters.
 *
 * @return int: Returns TRUE if a space character is found, otherwise FALSE.
 */

int	is_there_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == SPACE_CHAR)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

/**
 * is_empty - Checks if a string is empty or consists only of spaces.
 *
 * This function checks each character in the string to determine if it is
 * empty or only contains space characters. It returns TRUE if the string
 * is empty or contains only spaces; otherwise, it returns FALSE.
 *
 * @param str: The string to be checked for emptiness.
 *
 * @return int: Returns TRUE if the string is empty or only spaces; otherwise
 *              FALSE.
 */

int	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

/**
 * strdup_tillc - Duplicates a string until a space character is encountered.
 *
 * This function allocates memory for a new string and copies characters
 * from the original string until it encounters a space character. The new
 * string is null-terminated. If no space character is found, the entire
 * string is copied. The original string is freed after duplication.
 *
 * @param str: The string to be duplicated.
 *
 * @return char*: A pointer to the newly allocated string, or NULL if memory
 *                allocation fails.
 */

char	*strdup_tillc(char *str)
{
	int		i;
	char	*new_str;

	new_str = NULL;
	i = 0;
	while (str[i] != SPACE_CHAR)
		i++;
	new_str = (char *)my_calloc((i + 1), sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] != SPACE_CHAR)
			new_str[i] = str[i];
		else if (str[i] == SPACE_CHAR)
			break ;
		i++;
	}
	new_str[i] = '\0';
	free(str);
	return (new_str);
}
