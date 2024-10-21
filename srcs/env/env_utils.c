
#include "../../includes/minishell.h"

static void	change_sh_level(t_env *node);

/**
 * get_env - Initializes the environment variable linked list from environ.
 *
 * This function populates the `my_env` linked list in the command structure
 * using the global `environ` variable. It counts the number of environment
 * variables, creates the first node of the linked list, and then iteratively
 * adds each subsequent environment variable as a new node. Finally, it calls
 * `change_sh_level()` to update the shell level variable.
 *
 * @param command: The command structure to hold the environment variables.
 *
 * @return void: This function does not return a value.
 */

void	get_env(t_command *command)
{
	extern char	**environ;
	t_env		*temp;
	int			i;
	int			j;

	i = 0;
	j = 0;
	command->my_env = NULL;
	while (environ[i])
		i++;
	command->my_env = create_first_env_node(environ[j], command->my_env);
	temp = command->my_env;
	while (++j < i)
		temp = create_last_env_node(environ[j], temp);
	change_sh_level(command->my_env);
}

/**
 * my_getenv_by_list - Searches for an environment variable by key.
 *
 * This function traverses the linked list of environment variables and 
 * returns the node corresponding to the specified variable name. It compares
 * the provided name with the keys in the linked list and returns the first
 * match found.
 *
 * @param name: The name of the environment variable to search for.
 * @param my_env: The linked list of environment variables to search in.
 *
 * @return t_env*: A pointer to the environment variable node if found, 
 *                 otherwise NULL.
 */

t_env	*my_getenv_by_list(const char *name, t_env *my_env)
{
	t_env	*temp;
	int		size_key;

	temp = my_env;
	while (temp)
	{
		size_key = my_strlen(temp->key);
		if (my_strncmp(name, temp->key, size_key) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

/**
 * change_sh_level - Increments the shell level environment variable.
 *
 * This function retrieves the current shell level from the environment
 * variables, increments its value by one, and updates the variable in the
 * linked list. It allocates new memory for the updated value and frees the
 * old one.
 *
 * @param node: The linked list of environment variables containing SHLVL.
 *
 * @return void: This function does not return a value.
 */

static void	change_sh_level(t_env *node)
{
	t_env	*level;
	int		number;

	level = NULL;
	level = my_getenv_by_list("SHLVL", node);
	number = my_atoi(level->value) + 1;
	free(level->value);
	level->value = my_itoa(number);
}
