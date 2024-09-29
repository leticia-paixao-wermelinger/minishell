/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_exp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 00:50:46 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/26 09:41:17 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char *from_t_token_to_str(t_tokens *list);

char	*expand_heredoc_variables(char *str, t_env *env)
{
	t_tokens	*list;

	if (my_strlen(str) == 0)
		return (str);
	list = create_heredoc_list(str);
	search_dollar(list, env);
//	printf("ta fluindo... LISTA DO HEREDOC:\n");
//	print_tokens(list);
	free(str);
	str = from_t_token_to_str(list);
	free_t_tokens(list);
	return (str);
}

static char	*from_t_token_to_str(t_tokens *list)
{
	char		*str;
	t_tokens	*temp;

	temp = list;
	str = NULL;
	while (temp)
	{
		str = my_strjoin_cleaning(str, temp->word);
		temp = temp->next;
	}
	return (str);
}