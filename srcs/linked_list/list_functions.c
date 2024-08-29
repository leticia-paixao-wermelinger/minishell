/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:17:58 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/08/28 21:56:00 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*create_first_env_node(char *c, t_env *list)
{
	list = (t_env *)malloc(sizeof(t_env));
	list->key = my_strcdup(c, '=');
	list->value = fromstrcdup(c, '=');
	list->next = NULL;
	return (list);
}

t_env	*create_last_env_node(char	*c, t_env *prev)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	prev->next = new;
	new->key = my_strcdup(c, '=');
	new->value = fromstrcdup(c, '=');
	new->next = NULL;
	return (new);
}

t_node	*create_first_input_node(char *s, t_node *list)
{
	(void)s;
	list = (t_node *)malloc(sizeof(t_node));
	if (list == NULL)
		return (NULL);
	list->token = (t_tokens *)malloc(sizeof(t_tokens));
	if (list->token == NULL)
	{
		free(list);
		return (NULL);
	}
	// create token list
		//list->value = tokenize_sentence(s);
	list->fd_in = 0;
	list->fd_out = 1;
	list->pid = NO_INFO;
	list->exit_status = NO_INFO;
	list->next = NULL;
	return (list);
}

t_node	*create_last_input_node(char *s, t_node *prev)
{
	t_node	*new;

	(void)s;
	new = (t_node *)malloc(sizeof(t_node));
	new->token = (t_tokens *)malloc(sizeof(t_tokens));
	// create token list
		//list->value = tokenize_sentence(s);
	new->fd_in = 0;
	new->fd_out = 1;
	new->pid = NO_INFO;
	new->exit_status = NO_INFO;
	prev->next = new;
	//new->token = NO_INFO;
	new->next = NULL;
	return (new);
}

// A próxima função é para testes durante a elaboração do código:

void	printlist(t_node *list)
{
	t_node	*temp;
	int		i;

	temp = list;
	i = 1;
	while (temp)
	{
		printf("\033[0;33m Item %i, com endereço %p\n\033[0m", i, temp);
		printf("\033[0;31m"); // Make color red
		printf("Matriz\n");
		print_matrix(temp->value);
		printf("Token: %i\n", temp->token);
		printf("Next: %p\n\033[0m", temp->next);
		printf("\033[0m"); // Return to original color
		i++;
		temp = temp->next;
	}
}
