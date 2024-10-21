
#include "../../../includes/minishell.h"

/**
 * @brief env_list_size - Calculates the size of the environment list.
 *
 * This function traverses the linked list of environment variables
 * and counts the number of nodes in the list. It returns the total
 * count as an integer.
 *
 * @param list: A pointer to the head of the environment list.
 *
 * @return int: The number of nodes in the environment list.
 */

int	env_list_size(t_env *list)
{
	int	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

/**
 * @brief count_tokens_in_node - Counts tokens in a node of commands.
 *
 * This function counts all the tokens present in a linked list of
 * nodes representing commands. It iterates through each node and
 * sums the total number of tokens.
 *
 * @param sentence: A pointer to the head node of the command list.
 *
 * @return int: The total count of tokens in the command nodes.
 */

int	count_tokens_in_node(t_node *sentence)
{
	int			i;
	t_node		*node;
	t_tokens	*current_token;

	i = 0;
	node = sentence;
	while (node)
	{
		current_token = node->token;
		while (current_token)
		{
			i++;
			current_token = current_token->next;
		}
		node = node->next;
	}
	return (i);
}
