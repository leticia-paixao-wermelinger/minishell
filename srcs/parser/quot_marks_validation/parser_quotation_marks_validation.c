/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotation_marks_validation.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:07:12 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/07/22 00:16:53 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/*
** Modifica o input com caracteres não printáveis no lugar de metacaracteres
** que estejam no meio de aspas. Salta os caracteres que foram removidos
** em uma string, para poder retornar eles pro lugar posteriormente.
*/
void	change_invalid_metachars(t_command *command)
{
	int	i;
	int	flag_double;
	int	flag_simple;

	i = 0;
	flag_double = OFF;
	flag_simple = OFF;
	malloc_str_of_invalid_metas(command);
	while (command->input[i])
	{
		if (command->input[i] == DOUBLE_QUOT_MARK && flag_double == OFF)
			flag_double = ON;
		else if (command->input[i] == SIMPLE_QUOT_MARK && flag_simple == OFF)
		    flag_simple = ON;
		else if (is_metachar(command->input[i]) == TRUE && (flag_double == ON || flag_simple == ON))
		{
			add_meta_to_metastring(command, i);
			command->input[i] = UNPRINT_CHAR;
		}
		else if (command->input[i] == DOUBLE_QUOT_MARK && flag_double == ON)
			flag_double = OFF;
		else if (command->input[i] == SIMPLE_QUOT_MARK && flag_simple == ON)
			flag_simple = OFF;
		i++;
	}
//	printf("Teste de str de metachars: %s\n", command->invalid_metas);
}

char	**return_invalid_metas(t_command *command, char **matrix)
{
	int	i;
//	int	j;

	i = 0;
//	j = 0;
//	printf("\033[0;32m");
	while (matrix[i])
	{
//		printf("Antes de voltar c o metachar, com i = %d, string = %s\n", i, matrix[i]);
		return_added_unprinted_chars(matrix[i], command->invalid_metas);
//		printf("Depois de voltar c o metachar, com i = %d, string = %s\n", i, matrix[i]);
//		printf("\033[0m");
/*		while (matrix[i][j])
		{
			search_added_unprinted_chars();
			j++;
		}*/
		i++;
	}
	return (command->input_matrix);
}

static int	is_unprintable(char c)
{
	if (c == UNPRINT_CHAR)
		return (TRUE);
	return (FALSE);
}

void	return_added_unprinted_chars(char *s, char *metas)
{
	int			i;
	static int	j = 0;
	int			flag_double;
	int			flag_simple;

	i = 0;
	flag_double = OFF;
	flag_simple = OFF;
	while (s[i])
	{
		if (s[i] == DOUBLE_QUOT_MARK && flag_double == OFF)
			flag_double = ON;
		else if (s[i] == SIMPLE_QUOT_MARK && flag_simple == OFF)
		    flag_simple = ON;
		else if (is_unprintable(s[i]) == TRUE && (flag_double == ON || flag_simple == ON))
		{
			s[i] = metas[j];
			j++;
		}
		else if (s[i] == DOUBLE_QUOT_MARK && flag_double == ON)
			flag_double = OFF;
		else if (s[i] == SIMPLE_QUOT_MARK && flag_simple == ON)
			flag_simple = OFF;
		i++;
	}
}
