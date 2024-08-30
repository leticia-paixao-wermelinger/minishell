/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 00:36:05 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/08/30 18:31:57 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

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
	sentence = my_split(s, ' ');
	print_matrix(sentence);
	temp_word = list->token;
	list->token = (t_tokens *)malloc(sizeof(t_tokens));
	if (list->token == NULL)
	{
		free(list);
		return (NULL);
	}
	create_first_input_token(sentence[i], list->token);
	while (sentence[++i])
		temp_word = create_last_token(sentence[i], list->token);
	return (list->token);
}
