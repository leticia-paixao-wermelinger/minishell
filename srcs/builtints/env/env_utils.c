/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:32:50 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/08/05 23:37:29 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	get_env(t_command *command)
{
	extern char	**environ;
	t_node		*temp;
	int			i;
	int			j;

	i = 0;
	j = 0;
	command->my_env = NULL;
	while (environ[i])
		i++;
	command->my_env = create_first_env_node(environ[j], command->my_env);
	temp = command->my_env;
	while (++j < i)
		temp = create_last_env_node(environ[j], temp);
}

void	print_env_for_export(t_node *list)
{
	t_node	*temp;

	temp = list;
	while (temp)
	{
		my_printf("declare -x %s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}

t_node	*my_getenv_by_list(const char *name, t_node *my_env)
{
	t_node	*temp;
	int		size_key;

	temp = my_env;
	while (temp)
	{
		size_key = my_strlen(temp->key);
		if (my_strncmp(name, temp->key, size_key) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

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
//	printf("string antes de verificar aspas: %s\n", str);
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
	printf("Vai dar malloc em str2, de tamanho %i\n", j);
	str2 = (char *)malloc((j) * sizeof(char *));
	j = 0;
	flag_double = OFF;
	flag_simple = OFF;
	while (str[i])
	{
		printf("str[%i] == %c\n", i, str[i]);
		if (str[i] == DOUBLE_QUOT_MARK && flag_double == OFF)
		{
			printf("Aspas duplas, flag OFF\n");
			flag_double = ON;
		}
		else if (str[i] == SIMPLE_QUOT_MARK && flag_simple == OFF)
		{
			printf("Aspas simples, flag OFF\n");
			flag_simple = ON;
		}
		else if (str[i] == DOUBLE_QUOT_MARK && flag_double == ON)
		{
			//check_export_quot_error(str, i);
			printf("Printar erro de aspas duplas demais\n");
			break ;
		}
		else if (str[i] == SIMPLE_QUOT_MARK && flag_simple == ON)
		{
			//check_export_quot_error(str, i);
			printf("Printar erro de aspas simples demais\n");
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
