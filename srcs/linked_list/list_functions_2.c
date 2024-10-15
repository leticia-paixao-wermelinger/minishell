/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:20:04 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/15 00:36:37 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief create_last_token - Creates a new token and appends it to the token
 * list.
 *
 * This function allocates memory for a new token node, initializes its
 * word and type, and appends it to the end of the token list pointed to
 * by the previous token.
 *
 * @param word: The string to be assigned to the new token's word.
 * @param prev: A pointer to the last token in the list.
 *
 * @return t_tokens*: Returns a pointer to the newly created token node.
 *                    If memory allocation fails, returns NULL.
 *
 * @note The caller should ensure that the `prev` pointer is not NULL
 *       before calling this function. The new token's next pointer
 *       is set to NULL.
 */

t_tokens	*create_last_token(char *word, t_tokens *prev)
{
	t_tokens	*new;

	new = (t_tokens *)malloc(sizeof(t_tokens));
	if (!new)
		return (NULL);
	new->word = my_strdup(word);
	new->type = NO_INFO;
	prev->next = new;
	new->next = NULL;
	return (new);
}

/**
 * @brief print_tokens - Prints the details of each token in the token list.
 *
 * This function traverses the token list and prints the address of each
 * token, the address of its next pointer, its word, and its type.
 * Tokens with a NULL word are skipped.
 *
 * @param token: A pointer to the first token in the list to be printed.
 *
 * @note The function uses printf to display the details, and tokens
 *       with a NULL word are not printed.
 */

void	print_tokens(t_tokens *token)
{
	t_tokens	*temp;

	temp = token;
	while (temp)
	{
		if (token->word == NULL)
		{
			temp = temp->next;
			continue ;
		}
		printf("Endereço do token: %p\n", temp);
		printf("Endereço de next: %p\n", temp->next);
		printf("Word: %s\n", temp->word);
		printf("Type: %i\n", temp->type);
		temp = temp->next;
	}
}

/**
 * @brief printlist - Prints the details of each node in the node list.
 *
 * This function traverses the node list and prints the details of each
 * node, including its input token list, file descriptors, PID, and
 * exit status. The tokens of each node are printed by calling
 * `print_tokens`. Each node is numbered for easier identification.
 *
 * @param list: A pointer to the first node in the list to be printed.
 *
 * @note The function uses colored output to differentiate between
 *       different pieces of information. The addresses of the nodes
 *       and their tokens are also printed for debugging purposes.
 */

void	printlist(t_node *list)
{
	t_node	*temp;
	int		i;

	temp = list;
	i = 1;
	while (temp)
	{
		printf("\033[0;33m Item %i, com endereço %p\n\033[0m", i, temp);
		printf("\033[0;31m");
		printf("Matriz\n");
		printf("Endereço 1 token: %p\n", temp->token);
		printf("_________________________________________________\n");
		print_tokens(temp->token);
		printf("_________________________________________________\n");
		printf("fd_in: %i\n", temp->fd_in);
		printf("fd_out: %i\n", temp->fd_out);
		printf("pid: %i\n", temp->pid);
		printf("exit_status: %i\n", temp->exit_status);
		printf("Next: %p\n\033[0m", temp->next);
		printf("\033[0m");
		printf("Próximo:\n");
		i++;
		temp = temp->next;
	}
}
