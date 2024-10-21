
#include "../../../includes/minishell.h"

/**
 * @brief get_executable_path - Finds the executable path of a command.
 *
 * This function retrieves the executable path for a given command by
 * searching through directories listed in the PATH environment variable.
 * It returns the absolute path if found or NULL if not.
 *
 * @param command: A pointer to the command structure containing environment
 *                 variables.
 * @param node: A pointer to the node containing the command token.
 *
 * @return char*: The absolute path of the executable or NULL if not found.
 */

char	*get_executable_path(t_command *command, t_node *node)
{
	t_env	*get_path;
	char	*temp;
	char	**dir;
	char	*absolute_path;
	int		i;

	i = 0;
	get_path = my_getenv_by_list("PATH", command->my_env);
	if (!get_path)
		return (print_errno(node), NULL);
	dir = my_split(get_path->value, ':');
	if (!dir)
		return (NULL);
	while (dir[i])
	{
		temp = my_strjoin(dir[i], "/");
		absolute_path = my_strjoin(temp, node->token->word);
		free(temp);
		if (access(absolute_path, F_OK | X_OK) == 0)
			return (free_matrix(dir), absolute_path);
		free(absolute_path);
		i++;
	}
	return (print_errno(node), free_matrix(dir), NULL);
}

/**
 * @brief cmd_list_to_array - Converts a list of command tokens to an array.
 *
 * This function traverses a linked list of command tokens and converts
 * them into a dynamically allocated array of strings. It returns the
 * array of command arguments.
 *
 * @param sentences: A pointer to the head node of the command tokens.
 *
 * @return char**: An array of strings representing the command arguments
 *                 or NULL if an error occurs.
 */

char	**cmd_list_to_array(t_node *sentences)
{
	int			i;
	int			cmd_list_size;
	char		**args;
	t_tokens	*current_token;

	i = 0;
	cmd_list_size = count_tokens_in_node(sentences);
	args = malloc(sizeof(char *) * (cmd_list_size + 1));
	if (!args)
		return (print_error("Erro: alocação de cmd_list_to_array"), NULL);
	if (sentences)
	{
		current_token = sentences->token;
		while (current_token)
		{
			args[i] = my_strdup(current_token->word);
			if (!args[i])
				return (free_matrix(args), NULL);
			i++;
			current_token = current_token->next;
		}
	}
	args[i] = NULL;
	return (args);
}

/**
 * @brief envp_list_to_array - Converts an environment list to an array.
 *
 * This function converts a linked list of environment variables into a
 * dynamically allocated array of strings, with each string formatted as
 * "KEY=VALUE". It returns the array of environment strings.
 *
 * @param env_list: A pointer to the head of the environment list.
 *
 * @return char**: An array of strings representing environment variables
 *                 or NULL if an error occurs.
 */

char	**envp_list_to_array(t_env *env_list)
{
	int		i;
	char	**array;
	char	*temp;

	if (!env_list)
		return (NULL);
	i = env_list_size(env_list);
	array = malloc(sizeof(char *) * (i + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (env_list)
	{
		temp = my_strjoin(env_list->key, "=");
		array[i] = my_strjoin(temp, env_list->value);
		free(temp);
		if (!array[i])
			return (free_matrix(array), NULL);
		env_list = env_list->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
