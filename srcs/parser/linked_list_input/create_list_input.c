/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 00:36:05 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/18 17:29:12 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	make_list_from_input(t_command *command)
{
//	t_node		*list;
	int			i;
	t_node		*temp_sentence;

	i = 0;
//	command->l_input = NULL;
	command->l_input = create_first_input_node(command->input_matrix[i], command->l_input);
//	printf("Node 0:\n");
//	printlist(command->l_input);
	temp_sentence = command->l_input;
	while (command->input_matrix[++i])
	//{
		temp_sentence = create_last_input_node(command->input_matrix[i], temp_sentence);
		//printf("Node %i:\n", i);
		//printlist(command->l_input);
	//}
}

t_tokens	*make_list_tokens(char *s, t_node *list)
{
	t_tokens	*temp_word;
	char	    **sentence;
	int			i;

	i = 0;
	sentence = split_sentence_by_char(s, ' ');
//	sentence = my_split(s, ' ');
	print_matrix(sentence);
	list->token = (t_tokens *)malloc(sizeof(t_tokens));
	if (!(list->token))
	{
		free_sentences(sentence);
		free(list);
		return (NULL);
	}
	temp_word = list->token;
	create_first_input_token(sentence[i], temp_word);
	if (sentence[i] == NULL)
		return (list->token);
	while (sentence[++i])
	{
		temp_word = create_last_token(sentence[i], temp_word);
		if (!temp_word)
		{
			free_sentences(sentence);
			free_tokens(list->token);
			free(list);
			return (NULL);
		}
	}
	free_sentences(sentence);
	return (list->token);
}

void	free_sentences(char **sentences)
{
	int	i;

	i = 0;
	if (!sentences)
		return;
	while (sentences[i])
	{
		free(sentences[i]);
		i++;
	}
	free(sentences);
}

void	free_tokens(t_tokens *token)
{
	t_tokens	*temp;
	while (token)
	{
		temp = token->next;
		free(token->word);
		free(token);
		token = temp;
	}
}
