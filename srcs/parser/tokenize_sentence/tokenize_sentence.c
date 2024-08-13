/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_sentence.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:50:49 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/08/12 20:51:10 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char    **tokenize_sentence(char *input)
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