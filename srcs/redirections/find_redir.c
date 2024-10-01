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

static int	check_redir(t_node *temp, t_tokens *word, t_command *command);

int	redirections(t_node *sentence, t_command *command)
{
	t_node		*temp;
	t_tokens	*word;
	int			ret;

	temp = sentence;
	ret = NO_ERROR;
	while (temp)
	{
		word = temp->token;
		while (word)
		{
			printf("Está no loop de redurections com word = %s\n", word->word);
			if (token_is_redir(word) == TRUE)
				ret = check_redir(temp, word, command);
			if (word->next != NULL)
				check_redir(temp, word->next, command);
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

static int	check_redir(t_node *temp, t_tokens *word, t_command *command)
{
	int			ret;
	t_tokens	*jump;

	ret = 0;
	// Ajustar para quando a 1 posição for um redirect
	if (word->next->type == REDIR_APPEND)
		ret = do_append(temp, word);
	else if (word->next->type == REDIR_OUT)
		ret = do_redir_out(temp, word);
	else if (word->next->type == REDIR_IN)
		ret = do_redir_in(temp, word);
	else if (word->next->type == REDIR_HEREDOC)
	{
		printf("Vai chamar do_heredoc\n");
		ret = do_heredoc(temp, word, command->my_env, command);
	}
	else
		word = word->next;
	return (ret);
}