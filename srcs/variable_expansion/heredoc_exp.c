/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_exp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 00:50:46 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/10/15 00:15:59 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*from_t_token_to_str(t_tokens *list);

/**
 * @brief Expands environment variables in a heredoc string.
 *
 * This function processes the input string by expanding any environment
 * variables it contains. It first checks if the string is empty; if it is,
 * it returns the original string. If not, it creates a list of tokens
 * from the string, searches for dollar-prefixed variables, and constructs
 * a new string with the expanded values. The original string is freed to
 * avoid memory leaks.
 *
 * This function is crucial in a minishell context, as it allows the
 * user to include dynamic values in heredoc inputs by utilizing
 * environment variables.
 *
 * @param str The input string that may contain environment variables.
 * @param env The linked list of environment variables.
 * @return A newly allocated string with expanded variables, or the
 *         original string if it was empty.
 */

char	*expand_heredoc_variables(char *str, t_env *env)
{
	t_tokens	*list;

	if (my_strlen(str) == 0)
		return (str);
	list = create_heredoc_list(str);
	search_dollar(list, env);
	free(str);
	str = from_t_token_to_str(list);
	free_t_tokens(list);
	return (str);
}

/**
 * @brief Converts a linked list of tokens into a string.
 *
 * This function iterates through a linked list of tokens, concatenating
 * their words into a single dynamically allocated string. Memory is
 * managed by cleaning up the previous string during each iteration,
 * ensuring that no memory leaks occur. The resulting string is returned
 * to the caller for further use.
 *
 * This function supports the functionality of the minishell by
 * facilitating the transformation of tokenized inputs back into a
 * cohesive string, particularly after variable expansion in heredocs.
 *
 * @param list The linked list of tokens to be converted.
 * @return A newly allocated string representing the concatenated words
 *         from the token list.
 */

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
