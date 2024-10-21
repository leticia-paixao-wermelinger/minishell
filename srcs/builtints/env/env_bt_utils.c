
#include "../../../includes/minishell.h"

/**
 * print_env_for_export - Prints environment variables for 'export' command.
 *
 * This function prints the environment variables in a format suitable for the
 * 'export' command. Each variable is prefixed with "declare -x", followed by
 * the key and value, separated by an equals sign.
 *
 * @param list: A linked list of environment variables.
 * @param fd: The file descriptor to which the output will be written.
 *
 * @return void: This function does not return a value.
 */

void	print_env_for_export(t_env *list, int fd)
{
	t_env	*temp;

	temp = list;
	while (temp)
	{
		my_putstr_fd("declare -x ", fd);
		my_putstr_fd(temp->key, fd);
		my_putstr_fd("=", fd);
		my_putstr_fd(temp->value, fd);
		my_putstr_fd("\n", fd);
		temp = temp->next;
	}
}

/**
 * is_valid_ev - Checks if a string is a valid environment variable format.
 *
 * This function validates a given string to determine if it follows the correct
 * format for an environment variable. The first character must not be '=' and 
 * must be a valid export character. The string must contain an '=' sign to be
 * considered valid.
 *
 * @param str: The string to validate.
 *
 * @return int: Returns `NO_ERROR` if the string is valid, otherwise `ERROR`.
 */

int	is_valid_ev(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '=' && is_valid_exp_char(str[0]) == TRUE)
	{
		while (str[i])
		{
			if (is_valid_exp_char(str[i]) == TRUE)
				i++;
			else if (str[i] == '=')
				break ;
			else
				return (ERROR);
		}
	}
	else
		return (ERROR);
	if (str[i] == '=')
		i++;
	else
		return (ERROR);
	return (NO_ERROR);
}

/**
 * change_env_value - Changes the value of an existing environment variable.
 *
 * This function replaces the value of an environment variable with a new value.
 * It first frees the current value and then assigns a newly duplicated value.
 *
 * @param node: The environment variable node to modify.
 * @param str: The new value to assign to the environment variable.
 *
 * @return void: This function does not return a value.
 */

void	change_env_value(t_env *node, char *str)
{
	free(node->value);
	node->value = my_strdup(str);
}

/**
 * create_new_ev - Creates a new environment variable and adds it to the list.
 *
 * This function appends a new environment variable to the end of the environment
 * variable list. It creates the last node in the list with the provided string.
 *
 * @param str: The string representing the new environment variable.
 * @param env: The linked list of environment variables.
 *
 * @return void: This function does not return a value.
 */

void	create_new_ev(char *str, t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (temp->next == NULL)
		{
			create_last_env_node(str, temp);
			break ;
		}
		temp = temp->next;
	}
}
