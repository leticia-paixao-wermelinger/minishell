/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:17:58 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/10/15 00:35:37 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief create_first_env_node
- Creates the first environment node in the linked list.
 *
 * This function allocates memory for a new environment node and initializes
 * its key and value based on the provided string. The environment variable
 * is expected to be in the format "KEY=VALUE".
 *

* @param c: A string representing the environment variable in the format
"KEY=VALUE".

* @param list: A pointer to the current list of environment nodes (can be NULL).
 *
 * @return t_env*: Returns a pointer to the newly created environment node.
 *                 If memory allocation fails, returns NULL.
 *
 * @note This function does not handle memory cleanup for existing nodes in
 *       the list. The caller is responsible for managing the memory of
 *       the linked list.
 */

t_env	*create_first_env_node(char *c, t_env *list)
{
	list = (t_env *)malloc(sizeof(t_env));
	list->key = my_strcdup(c, '=');
	list->value = fromstrcdup(c, '=');
	list->next = NULL;
	return (list);
}

/**
 * @brief create_last_env_node
- Creates a new environment node and appends it to the list.
 *
 * This function allocates memory for a new environment node and initializes
 * its key and value based on the provided string. The environment variable
 * is expected to be in the format "KEY=VALUE". The new node is appended to
 * the end of the linked list pointed to by the previous node.
 *

* @param c: A string representing the environment variable in the format
"KEY=VALUE".
 * @param prev: A pointer to the last environment node in the list.
 *
 * @return t_env*: Returns a pointer to the newly created environment node.
 *                 If memory allocation fails, returns NULL.
 *
 * @note The caller should ensure that the `prev` pointer is not NULL
 *       before calling this function.
 */

t_env	*create_last_env_node(char *c, t_env *prev)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	prev->next = new;
	new->key = my_strcdup(c, '=');
	new->value = fromstrcdup(c, '=');
	new->next = NULL;
	return (new);
}

/**
 * @brief create_first_input_node
- Creates the first input node in the linked list.
 *
 * This function allocates memory for a new input node and initializes it
 * based on the provided string. It creates a list of tokens from the input
 * string, setting up the input/output file descriptors and process ID.
 *
 * @param s: The input string to be tokenized and stored in the node.
 * @param list: A pointer to the current list of input nodes (can be NULL).
 *
 * @return t_node*: Returns a pointer to the newly created input node.
 *                  If memory allocation fails, returns NULL.
 *
 * @note This function is responsible for initializing the node's fields to
 *       appropriate default values (e.g., file descriptors, PID).
 */

t_node	*create_first_input_node(char *s, t_node *list)
{
	list = (t_node *)malloc(sizeof(t_node));
	if (list == NULL)
		return (NULL);
	make_list_tokens(s, list);
	list->fd_in = 0;
	list->fd_out = 1;
	list->pid = -2;
	list->exit_status = NO_INFO;
	list->next = NULL;
	return (list);
}

/**
 * @brief create_last_input_node
- Creates a new input node and appends it to the list.
 *
 * This function allocates memory for a new input node and initializes it
 * based on the provided string. It creates a list of tokens from the input
 * string and appends the new node to the end of the linked list pointed to
 * by the previous node.
 *
 * @param s: The input string to be tokenized and stored in the new node.
 * @param prev: A pointer to the last input node in the list.
 *
 * @return t_node*: Returns a pointer to the newly created input node.
 *                  If memory allocation fails, returns NULL.
 *
 * @note The caller should ensure that the `prev` pointer is not NULL
 *       before calling this function.
 */

t_node	*create_last_input_node(char *s, t_node *prev)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	make_list_tokens(s, new);
	new->fd_in = 0;
	new->fd_out = 1;
	new->pid = -2;
	new->exit_status = NO_INFO;
	prev->next = new;
	new->next = NULL;
	return (new);
}

/**
 * @brief create_first_input_token
- Initializes the first token in the token list.
 *
 * This function creates the first token in a list of tokens by setting its
 * word and type. The token is initialized with the provided word, which is
 * duplicated to allocate memory for it. If the word is NULL, the token's
 * word is also set to NULL.
 *
 * @param word: The string to be assigned to the token's word.

* @param list: A pointer to the token list where the first token will be
created.
 *

* @note The token's type is initialized to NO_INFO and the next pointer is set
to NULL.
 */

void	create_first_input_token(char *word, t_tokens *list)
{
	if (!word)
		list->word = NULL;
	else
		list->word = my_strdup(word);
	list->type = NO_INFO;
	list->next = NULL;
}
