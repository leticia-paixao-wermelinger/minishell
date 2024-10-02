/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:41:24 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/26 00:34:58 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * parser - Parses the given command.
 * 
 * This function performs an initial error validation, primarily focused on 
 * syntax errors in the user's input. It then splits the input string by pipes, 
 * creates a list from the processed input, and performs additional validations. 
 * If any errors are detected during parsing, the function clears the relevant 
 * data structures and returns an error code.
 *
 * @param command: A pointer to the t_command structure that holds the user's 
 * input and necessary information for Bash processing.
 *
 * @return int: Returns NO_ERROR if parsing is successful, or ERROR if any 
 * validation or processing fails.
 */

int	parser(t_command *command)
{
	if (first_input_validation(command) == ERROR)
	{
		clear_input(command);
		return (ERROR);
	}
	command->input_matrix = split_sentence_by_char(command->input, '|');
	make_list_from_input(command);
	my_clean_vect(command->input_matrix);
	command->input_matrix = NULL;
	search_tokens(command->l_input);
	if (general_input_validation(command->l_input) == ERROR)
	{
		clear_loop_end(command);
		return (ERROR);
	}
//Imprimir a lista para teste
	//printlist(command->l_input);
	return (NO_ERROR);
}

/**
 * split_sentence_by_char - Splits a string by a given character, 
 * respecting the quote state.
 *
 * This function iterates through the input string, checking if the characters 
 * are inside single or double quotes. If they are not inside quotes, the function 
 * replaces the separator character with a non-printable character (UNPRINT_CHAR) 
 * to facilitate splitting later.
 *
 * @param input: The input string to be split.
 * @param c: The character by which the string will be split.
 *
 * @return char**: A vector of strings resulting from the original string split.
 */

char    **split_sentence_by_char(char *input, char c)
{
    int quote_state;
    int i;

    quote_state = 0;
    i = 0;
    while (input[i])
    {
            if (is_simple_quote(input[i]) && (quote_state == 0 || quote_state == 1))
                quote_state ^= 1;
            else if (is_double_quote(input[i]) && (quote_state == 0 || quote_state == 2))
                quote_state ^= 2;
            else if (is_char(input[i], c) && quote_state == 0)
                    input[i] = UNPRINT_CHAR;
            i++;
    }
    return (my_split(input, UNPRINT_CHAR));
}