
#include "../../includes/minishell.h"

/**
 * @brief Extracts the name of a variable from a string.
 *
 * This function retrieves the name of a variable from the provided string `str`
 * starting at index `j`. It identifies valid variable characters (letters,
 * digits, or underscores) and returns a dynamically allocated string containing
 * the variable name. This is essential for correctly parsing variable names in
 * minishell.
 *
 * @param str The string from which to extract the variable name.
 * @param j The starting index for extraction.
 * @return A dynamically allocated string representing the variable name,
 *         or NULL on memory allocation failure.
 */

char	*take_name_var(char *str, int j)
{
	int		i;
	int		size;
	char	*name;

	i = j;
	size = 0;
	while (str[i] && (my_isalpha(str[i]) != 0 || my_isdigit(str[i]) != 0
			|| str[i] == '_'))
	{
		size++;
		i++;
	}
	name = (char *)malloc((size + 1) * sizeof(char));
	if (!name)
		return (NULL);
	size = 0;
	while (str[j] && j < i)
	{
		name[size] = str[j];
		size++;
		j++;
	}
	name[size] = '\0';
	return (name);
}
