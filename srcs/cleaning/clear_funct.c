
#include "../../includes/minishell.h"

/**
 * free_list - Frees a linked list of nodes.
 *
 * This function iterates through the linked list of nodes, freeing each node
 * and its associated token data. It calls `free_t_tokens()` to free the token
 * structure for each node.
 *
 * @param list: A linked list of nodes to be freed.
 *
 * @return void: This function does not return a value.
 */

void	free_list(t_node *list)
{
	t_node		*temp;
	t_node		*next_node;
	t_tokens	*temp_token;

	while (list)
	{
		temp = list;
		temp_token = temp->token;
		free_t_tokens(temp_token);
		next_node = list->next;
		free(temp);
		temp = NULL;
		list = next_node;
	}
}

/**
 * free_t_tokens - Frees a linked list of token nodes.
 *
 * This function iterates through the linked list of token nodes, freeing each
 * token's word and the token itself.
 *
 * @param node: A linked list of tokens to be freed.
 *
 * @return void: This function does not return a value.
 */

void	free_t_tokens(t_tokens *node)
{
	t_tokens	*next_token;

	next_token = NULL;
	while (node)
	{
		next_token = node->next;
		free(node->word);
		node->word = NULL;
		free(node);
		node = NULL;
		node = next_token;
	}
}

/**
 * free_env - Frees a linked list of environment variables.
 *
 * This function iterates through the linked list of environment variables,
 * freeing both the key and value for each variable before freeing the node
 * itself.
 *
 * @param list: A linked list of environment variables to be freed.
 *
 * @return void: This function does not return a value.
 */

void	free_env(t_env *list)
{
	t_env	*temp;

	while (list)
	{
		temp = list;
		free(temp->key);
		temp->key = NULL;
		free(temp->value);
		temp->value = NULL;
		list = list->next;
		free(temp);
		temp = NULL;
	}
}
