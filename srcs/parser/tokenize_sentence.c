/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_sentence.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:50:49 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/18 17:18:19 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * tokenize_sentence - Splits a string into tokens based on spaces, while handling quotes.
 * 
 * This function processes an input string, replacing spaces with a unique character 
 * (`UNPRINT_CHAR`) when they are outside of quoted sections. It handles both single 
 * and double quotes by tracking the current quote state, ensuring that spaces inside 
 * quotes are preserved. The string is then split into tokens using the custom `my_split` function.
 *
 * @param input: The input string to be tokenized, which is a command line entered by the user.
 *
 * @return char**: A pointer to an array of strings (tokens) that represent the individual 
 * parts of the input command.
 */

char	**tokenize_sentence(char *input)
{
	int	quote_state;
	int	i;

	quote_state = 0;
	i = 0;
	while (input[i])
	{
		if (is_simple_quote(input[i]) && (quote_state == 0 || quote_state == 1))
			quote_state ^= 1;
		else if (is_double_quote(input[i]) && (quote_state == 0 || \
				quote_state == 2))
			quote_state ^= 2;
		else if (input[i] == SPACE_CHAR && quote_state == 0)
			input[i] = UNPRINT_CHAR;
		i++;
	}
	return (my_split(input, UNPRINT_CHAR));
}
