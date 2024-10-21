
#include "../../../includes/minishell.h"

/**
 * @brief free_matrix - Frees a dynamically allocated matrix of strings.
 *
 * This function iterates through the given matrix, freeing each
 * string element. After freeing all strings, it frees the matrix
 * itself to prevent memory leaks.
 *
 * @param matrix: A pointer to the matrix of strings to be freed.
 *
 * @return void: This function does not return a value.
 */

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

/**
 * @brief execve_clean - Cleans up memory used by command arguments and env.
 *
 * This function frees the memory allocated for both the command
 * arguments and the environment variable array, ensuring that there
 * are no memory leaks after executing a command.
 *
 * @param args: The array of command arguments to be freed.
 * @param env_array: The environment variable array to be freed.
 *
 * @return void: This function does not return a value.
 */

void	execve_clean(char **args, char **env_array)
{
	free_matrix(args);
	free_matrix(env_array);
}
