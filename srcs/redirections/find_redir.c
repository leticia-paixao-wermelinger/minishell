/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 23:51:30 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/26 09:42:36 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_redir(t_node *temp, t_tokens *word, t_command *command, int first_flag);

int	redirections(t_node *sentence, t_command *command)
{
	t_node		*temp;
	t_tokens	*word;
	t_tokens	*temp_token;
	int			ret;
	int			flag_first;

	temp = sentence;
	temp_token = NULL;
	ret = NO_ERROR;
	flag_first = ON;
	while (temp)
	{
		word = temp->token;
		while (word)
		{
			printf("Está no loop de redurections com word = %s\n", word->word);
			if (flag_first == ON)
			{
				printf("1 condução de first flag\n");
				if (token_is_redir(word) == TRUE)
				{
					printf("1 token é redir\n");
					temp_token = word;
					sentence->token = word->next->next;
					ret = check_redir(temp, temp_token, command, flag_first);
				}
				flag_first = OFF;
			}
			else if (word->next != NULL)
			{
				ret = check_redir(temp, word, command, flag_first);
				printf("Saiu da check_redir com %p, que aponta para: %s\n", word, word->word);
				if (ret == -1)
					word = word->next;
			}
			else
				word = word->next;
			if (ret == ERROR)
				return (ERROR);
		}
		temp = temp->next;
	}
	printf("Vai retornar com a estrutura:\n");
	printlist(command->l_input);
	return (ret);
}

// teste: echo oieoieee > out1 > out2 > out3

static int	check_redir(t_node *temp, t_tokens *word, t_command *command, int first_flag)
{
	int			ret;
	t_tokens	*node;

	ret = -1;
	printf("Função check_redir recebeu o endereço %p, que aponta para: %s e c a first_flag = %i\n", word, word->word, first_flag);
	if (first_flag != ON)
	{
		printf("Entrou no if de first_flag com o endereço %p, que aponta para: %s\n", word, word->word);
		node = word->next;
		printf("Saiu do if de first_flag com o endereço %p, que aponta para: %s\n", word, word->word);

	}
	else
	{
		node = word;
	//	word = word->next->next;
	}
	if (node->type == REDIR_APPEND)
		ret = do_append(temp, node);
	else if (node->type == REDIR_OUT)
	{
		printf("Vai chamar do_redir_out\n");
		ret = do_redir_out(temp, node);
	}
	else if (node->type == REDIR_IN)
		ret = do_redir_in(temp, node);
	else if (node->type == REDIR_HEREDOC)
	{
		printf("Vai chamar do_heredoc\n");
		ret = do_heredoc(temp, node, command->my_env, command);
	}
/*	else
		word = word->next;*/
	printf("Está saindo da funçao check_redir com o endereço %p, que aponta para: %s\n", word, word->word);
	return (ret);
}