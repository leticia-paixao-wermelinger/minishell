/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:41:24 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/07/08 19:05:21 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_parser(t_command *command)
{
	search_invalid_metachars(command);
//	my_printf("Ajuste pré split c/ espaços: %s\n", command->input);
	command->input = check_invalid_successive_metachars(command->input);
	command->input = remove_spaces_around_metachars(command->input);
	my_printf("Ajuste pré split s/ espaços: %s\n", command->input);
	//split de metacaracteres
	command->input_matrix = meta_split(command->input);
//	my_printf("Input pós split de metacaracteres:\n");
//	print_matrix(command->input_matrix);
	//return_invalid_pipes
}

void	search_invalid_metachars(t_command *command)
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

char	*remove_spaces_around_metachars(char *s)
{
	int		new_size;
	char	*str;

	new_size = strlen_without_spaces_post_metachars(s);
	str = (char *)malloc((new_size + 1) * sizeof(char));
	remove_spaces_after_metachars(s, str);
	free(s);
	new_size = strlen_without_spaces_before_metachars(str);
	s = (char *)malloc((new_size + 1) * sizeof(char));
	remove_spaces_before_metachars(str, s, new_size);
	free(str);
	return (s);
}

void	remove_spaces_after_metachars(char *s, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		str[j] = s[i];
		j++;
		if (is_metachar(s[i]) == TRUE)
		{
			i++;
			while (s[i] == SPACE_CHAR)
				i++;
		}
		else
			i++;
	}
	str[j] = '\0';
}

void    remove_spaces_before_metachars(char *s, char *str, int final_size)
{
	int		i;
	int		j;

	i = my_strlen(s);
	j = final_size;
//	printf("\033[0;33mremove_spaces_before_metachars");
//	printf("String: %s\n", s);
//	printf("Fora do while: i = %i & j = %i\n", i , j);
	str[j] = '\0';
	while (i >= 0)
	{
//		printf("Dentro do while: i = %i & j = %i\n", i , j);
		str[j] = s[i];
//		printf("str[%i] = %c & s[%i] = %c\n", j, str[j], i, s[i]);
		j--;
		if (is_metachar(s[i]) == TRUE)
		{
			i--;
			while (s[i] == SPACE_CHAR)
				i--;
		}
		else
			i--;
	}
	printf("\033[0m");
}
