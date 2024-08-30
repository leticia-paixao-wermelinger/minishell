/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:41:24 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/08/30 16:26:47 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	parser(t_command *command)
{
	//VAlIDAR PIPES DUPLOS!
	command->input_matrix = split_sentences(command->input);
	my_printf("Matriz pós split:\n");
	print_matrix(command->input_matrix);
	make_list_from_input(command);
	my_clean_vect(command->input_matrix);
	//Imprimir a lista para teste
	printlist(command->l_input);
}

char    **split_sentences(char *input)
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
            else if (is_pipe(input[i]) && quote_state == 0) //sem aspas ao redor do pipe
                    input[i] = UNPRINT_CHAR;
            i++;
    }
    return (my_split(input, UNPRINT_CHAR));
}
