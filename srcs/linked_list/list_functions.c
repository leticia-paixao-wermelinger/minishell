/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:17:58 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/24 14:20:06 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	if (list == NULL)
		return (NULL);
	make_list_tokens(s, list);
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

	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	make_list_tokens(s, new);
	new->fd_in = 0;
	new->fd_out = 1;
	new->pid = NO_INFO;
	new->exit_status = NO_INFO;
	prev->next = new;
	new->next = NULL;
	return (new);
}

void	create_first_input_token(char *word, t_tokens *list)
{
	if (!word)
		list->word = NULL;
	else
		list->word = my_strdup(word);
	list->type = NO_INFO;
	list->next = NULL;
}

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

// As próximas 2 funções são para testes durante a elaboração do código:

static void	print_tokens(t_tokens *token)
{
	t_tokens	*temp;
	int			i = 0;

	temp = token;
	while (temp)
	{
		if (token->word == NULL)
		{
			temp = temp->next;
			continue ;
		}
		printf("Word: %s\n", temp->word);
		i = 0;
/*		while (temp->word[i])
		{
			printf("Endereço de %c: %p\n", temp->word[i], &temp->word[i]);
			i++;
		}*/
//		printf("Endereço de %c: %p\n", temp->word[i], &temp->word[i]);
		printf("Type: %i\n", temp->type);
		temp = temp->next;
	}
}

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
		printf("Endereço 1 token: %p\n", temp->token);
		printf("_________________________________________________\n");
		print_tokens(temp->token);
		printf("_________________________________________________\n");
		printf("fd_in: %i\n", temp->fd_in);
		printf("fd_out: %i\n", temp->fd_out);
		printf("pid: %i\n", temp->pid);
		printf("exit_status: %i\n", temp->exit_status);
		printf("Next: %p\n\033[0m", temp->next);
		printf("\033[0m"); // Return to original color
		printf("Próximo:\n");
		i++;
		temp = temp->next;
	}
}
