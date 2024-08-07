/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:17:58 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/07/26 14:12:57 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_node	*create_first_env_node(char *c, t_node *list)
{
	list = (t_node *)malloc(sizeof(t_node));
	list->key = my_strcdup(c, '=');
	list->value = fromstrcdup(c, '=');
	list->token = NO_INFO;
	list->next = NULL;
	return (list);
}

t_node	*create_last_env_node(char	*c, t_node *prev)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	prev->next = new;
	new->key = my_strcdup(c, '=');
	new->value = fromstrcdup(c, '=');
	new->token = NO_INFO;
	new->next = NULL;
	return (new);
}

t_node	*create_first_input_node(char *s, t_node *list)
{
	list = (t_node *)malloc(sizeof(t_node));
	list->key = NULL;
	list->value = my_strdup(s);
	list->token = NO_INFO;
	list->next = NULL;
	return (list);
}

t_node	*create_last_input_node(char *s, t_node *prev)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	prev->next = new;
	new->key = NULL;
	new->value = my_strdup(s);
	new->token = NO_INFO;
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
		printf("Key: %s\n", temp->key);
		printf("\033[0;34mValue: %s\n\033[0;31m", temp->value);
		printf("Token: %i\n", temp->token);
		printf("Next: %p\n\033[0m", temp->next);
		printf("\033[0m"); // Return to original color
		i++;
		temp = temp->next;
	}
}
