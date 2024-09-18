/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:32:50 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/18 17:29:12 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	print_env_for_export(t_env *list, int fd)
{
	t_env	*temp;

	temp = list;
	while (temp)
	{
		my_putstr_fd("declare -x ", fd);
		my_putstr_fd(temp->key, fd);
		my_putstr_fd("=", fd);
		my_putstr_fd(temp->value, fd);
		my_putstr_fd("\n", fd);
		//my_printf("declare -x %s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}

int	is_valid_ev(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '=' && is_valid_exp_char(str[0]) == TRUE)
	{
		while (str[i])
		{
			if (is_valid_exp_char(str[i]) == TRUE)
				i++;
			else if (str[i] == '=')
				break ;
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
	return (NO_ERROR);
}

void	change_env_value(t_env *node, char *str)
{
	free(node->value);
	node->value = my_strdup(str);
}

void	create_new_ev(char *str, t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (temp->next == NULL)
		{
			create_last_env_node(str, temp);
			break ;
		}
		temp = temp->next;
	}
}

// -----------------------------------------------------------------
/*
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
}*/
