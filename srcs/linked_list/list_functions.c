/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:17:58 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/08/12 15:12:51 by lpaixao-         ###   ########.fr       */
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
	list = (t_node *)malloc(sizeof(t_node));
//	list->value = my_strdup(s); // No lugar de dar dup, chamar a função que vai chamar a split de espaços
	list->value = tokenize_sentence(s);
	list->token = NO_INFO;
	list->next = NULL;
	return (list);
}

t_node	*create_last_input_node(char *s, t_node *prev)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	prev->next = new;
	//new->value = my_strdup(s);
	new->value = tokenize_sentence(s);
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
		print_matrix(temp->value);
		printf("Token: %i\n", temp->token);
		printf("Next: %p\n\033[0m", temp->next);
		printf("\033[0m"); // Return to original color
		i++;
		temp = temp->next;
	}
}
