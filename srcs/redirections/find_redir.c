/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 23:51:30 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/10/07 20:39:36 by lraggio          ###   ########.fr       */
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
//	printf("1. Vai passar redirects na estrutura:\n");
//	printlist(command->l_input);
	while (temp)
	{
		word = temp->token;
		flag_first = ON;
		while (word)
		{
//			printf("1. Está no loop de redirections com word = %s\n", word->word);
			if (flag_first == ON)
			{
//				printf("1 condução de first flag\n");
				while (word && token_is_redir(word) == TRUE)
				{
//					printf("2. 1 token é redir\n");
//					printf("sentence->token->word == %s\n", sentence->token->word);
//					printf("word == %s\n", word->word);
					temp_token = word;
					ret = check_redir(temp, temp_token, command, flag_first);
					if (temp->token != NULL)
						word = temp->token;
					else
						word = NULL;
					if (ret == ERROR)
						temp->exit_status = 1;
//					printf("3. Está no momento com a estrutura:\n");
//					printlist(command->l_input);
//					printf("3.2. pós check_redir está no nó == %p, com %s\n", word, word->word);
//					word = temp->token->next;
				}
				flag_first = OFF;
			}
			if (!(sentence->token))
			{
				sentence->token = NULL;
				return (ret);
			}
//			printf("4. Endereço de word (%s) = %p\n", word->word, word);
			if (word != NULL)
			{
				if (word->next != NULL)
				{
					ret = check_redir(temp, word, command, flag_first);
//					printf("5. Saiu da check_redir com %p, que aponta para: %s\n", word, word->word);
					if (ret == -1)
						word = word->next;
				}
				else
					word = word->next;
			}
			if (ret == ERROR)
			{
				//printf("Vai retornar com a estrutura:\n");
				//printlist(command->l_input);
				return (ERROR);
			}
		}
//		printf("6. Deu pipe\n");
		temp = temp->next;
	}
	printf("Vai retornar com a estrutura:\n");
	printlist(command->l_input);
	return (ret);
}

static int	check_redir(t_node *sentence, t_tokens *word, t_command *command, int first_flag)
{
	int			ret;
	t_tokens	*node_token;

	ret = -1;
//	printf("Função check_redir recebeu o endereço %p, que aponta para: %s e c a first_flag = %i\n", word, word->word, first_flag);
//	printf("sentence->token->word em check_redir == %s\n", sentence->token->word);
	if (first_flag != ON)
	{
//		printf("Entrou no if de first_flag com o endereço %p, que aponta para: %s\n", word, word->word);
		node_token = word->next;
//		printf("sentence->token->word em check_redir == %s\n", sentence->token->word);
//		printf("Saiu do if de first_flag com o endereço %p, que aponta para: %s\n", word, word->word);
	}
	else
	{
		node_token = word;
//		printf("no else: sentence->token->word em check_redir == %s\n", sentence->token->word);
	//	word = word->next->next;
	}
	if (node_token->type == REDIR_APPEND)
		ret = do_append(sentence, node_token);
	else if (node_token->type == REDIR_OUT)
	{
//		printf("Vai chamar do_redir_out\n");
		ret = do_redir_out(sentence, node_token);
	}
	else if (node_token->type == REDIR_IN)
		ret = do_redir_in(sentence, node_token);
	else if (node_token->type == REDIR_HEREDOC)
	{
//		printf("Vai chamar do_heredoc com sentence == %p e sentence->token == %p\n", sentence, sentence->token);
		ret = do_heredoc(sentence, node_token, command);
	}
/*	else
		word = word->next;*/
	//printf("Está saindo da funçao check_redir com o endereço %p, que aponta para: %s\n", sentence->token, sentence->token->word);
	return (ret);
}