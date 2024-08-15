/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:32:50 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/08/14 17:14:29 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	print_env_for_export(t_env *list)
{
	t_env	*temp;

	temp = list;
	while (temp)
	{
		my_printf("declare -x %s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}

int	is_valid_ev(char *str)
{
	int	i;

	i = 0;
	if (is_valid_exp_char(str[i]) == TRUE)
	{
		while (is_valid_exp_char(str[i]) == TRUE)
		{
			if (is_valid_exp_char(str[i]) == TRUE)
				i++;
			else
				return (ERROR);
		}
	}
	else
		return (ERROR);
	if (str[i] == '=')
		i++;
	else
		return (ERROR);
	while (is_valid_exp_char(str[i]) == TRUE) // Válidos: #
	{
		//if ()
		i++;
	}
	return (NO_ERROR);
}

// -----------------------------------------------------------------

int	check_export_error(char **str)
{
	int		i;
	char	*str2;

	i = 0;
	str2 = NULL;
//	printf("\033[0;33mStr = |%s| e str2 = |%s|\n", *str, str2);
	while ((*str)[i])
	{
		if ((*str)[i] == SPACE_CHAR)
		{
			str2 = fromstrcdup(*str, SPACE_CHAR);
//			printf("Depois de fromstrcdup: Str = |%s| e str2 = |%s|\n", *str, str2);
			free(*str);
			*str = str2;
//			free(str2);
//			printf("Antes de dar break: Str = |%s| e str2 = |%s|\n", *str, str2);
			break ;
		}
		if ((*str)[i] == '=')
			return (NO_ERROR);
		i++;
	}
	printf("bash: export: `%s': not a valid identifier\033[0m\n", *str);
	return (ERROR);
}

char	*validate_quot_marks_for_export(char *str)
{
	int		i;
	int		j;
	int		flag_double;
	int		flag_simple;
	char	*str2;

	i = 0;
	j = 0;
	flag_double = OFF;
	flag_simple = OFF;
	while (str[j])
	{
		if (str[j] == DOUBLE_QUOT_MARK && flag_double == OFF)
			flag_double = ON;
		else if (str[j] == SIMPLE_QUOT_MARK && flag_simple == OFF)
			flag_simple = ON;
		else if (str[j] == DOUBLE_QUOT_MARK && flag_double == ON)
			break ;
		else if (str[j] == SIMPLE_QUOT_MARK && flag_simple == ON)
			break ;
		j++;
	}
	str2 = (char *)malloc((j) * sizeof(char *));
	j = 0;
	flag_double = OFF;
	flag_simple = OFF;
	while (str[i])
	{
		if (str[i] == DOUBLE_QUOT_MARK && flag_double == OFF)
			flag_double = ON;
		else if (str[i] == SIMPLE_QUOT_MARK && flag_simple == OFF)
			flag_simple = ON;
		else if (str[i] == DOUBLE_QUOT_MARK && flag_double == ON)
		{
			//check_export_quot_error(str, i);
			printf("Chegou na 2 aspas duplas\n");
			break ;
		}
		else if (str[i] == SIMPLE_QUOT_MARK && flag_simple == ON)
		{
			//check_export_quot_error(str, i);
			printf("Chegou na 2 aspas simples\n");
			break ;
		}
		else
		{
			printf("Salvando valor|%c| em str2, ", str[i]);
			str2[j] = str[i];
			printf("str2 ficando |%c|\n", str2[j]);
			j++;
		}
		i++;
	}
	str2[j] = '\0';
	return (str2);
}
