/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:41:24 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/07/01 21:14:32 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_parser(t_command *command)
{
	search_invalid_metachars(command);//só tem q fazer essa validação p pipes? e pros demais metacaracteres?
	my_printf("Ajuste pré split c/ espaços: %s\n", command->input);
	remove_spaces_around_metachars(command->input);
	my_printf("Ajuste pré split s/ espaços: %s\n", command->input);
	//split de metacaracteres
	//command->input_matrix = meta_split(command->input);
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
	while (command->input[i])
	{
		if (command->input[i] == DOUBLE_QUOT_MARK && flag_double == OFF)
			flag_double = ON;
		else if (command->input[i] == SIMPLE_QUOT_MARK && flag_simple == OFF)
			flag_simple = ON;
		else if (is_metachar(command->input[i]) == TRUE && (flag_double == ON || flag_simple == ON))
			command->input[i] = UNPRINT_CHAR;
		else if (command->input[i] == DOUBLE_QUOT_MARK && flag_double == ON)
			flag_double = OFF;
		else if (command->input[i] == SIMPLE_QUOT_MARK && flag_simple == ON)
			flag_simple = OFF;
		i++;
	}
}

void	remove_spaces_around_metachars(char *s)
{
	int		new_size;
	char	*str;

	new_size = strlen_without_spaces_post_metachars(s);
//	my_printf("Tamanho original: %i\n", my_strlen(s));
//	my_printf("Tamanho s/ espaços: %i\n", new_size);
	str = (char *)malloc((new_size + 1) * sizeof(char));
	remove_spaces_after_metachars(s, str);
	printf("Vai dar o 1 free. Str está assim: %s\n", str);
	free(s);
	new_size = strlen_without_spaces_before_metachars(str);
	s = (char *)malloc((new_size + 1) * sizeof(char));
	remove_spaces_before_metachars(str, s, new_size);
	printf("Vai dar o 2 free. s está assim: %s\n", s);
	free(str);
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
	j = final_size + 1;
	str[j] = '\0';
	while (i >= 0)
	{
		str[j] = s[i];
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
}
