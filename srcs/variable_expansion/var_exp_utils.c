/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_exp_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:29:59 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/04 19:38:06 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern unsigned int   g_status;

static char	*take_name_var(char *str, int j);

int	print_global_var(t_tokens *token, char *str, int j)
{
	char	*number;
	char	*temp;
	int		index;

	number = my_itoa(g_status);
	index = my_strlen(number);
	temp = join_strs(str, number, (j - 1), 1, &index);
	free(token->word);
	token->word = my_strdup(temp); 
	free(temp);
	free(number);
//	printf("Ao final de print_global_var, index = %i, list->value[index] = %c\n", index, token->word[index]);
	return (index);
}

int	double_dollar(t_tokens *token, char *str, int j)
{
	int		index;
	char	*temp;

	index = 0;
	temp = join_strs(str, "$", (j - 1), 1, &index);
	free(token->word);
	token->word = my_strdup(temp); 
	free(temp);
	index++;
//	printf("Ao final de double_dollar, index = %i, list->value[index] = %c\n", index, token->word[index]);
	return (index);
}

int	expand_variable(t_tokens *token, t_env *env, char *str, int j)
{
	int		index;
	char	*temp;
	char	*key;
	t_env	*node;

	index = 0;
	key = take_name_var(str, j);
	printf("KEY == %s\n", key);
	if ()
	if (!key)
	{
		// fazer essa validação!
		return (j - 1);
	}
	node = my_getenv_by_list(key, env);
	printf("NODE->KEY == %s && NODE-VALUE == %s\n", node->key, node->value);
	printf("node->value = %s & jump = %zu\n", node->value, my_strlen(node->key));
	temp = join_strs(str, node->value, (j - 1), (my_strlen(node->key)), &index);
	free(token->word);
	token->word = my_strdup(temp);
	free(temp);
	free(key);
	printf("Ao final de expand_variable, index = %i, token->word[index] = %c\n", index, token->word[index]);
	return (index);
}

char	*join_strs(char *str, char *middle, int j, int jump, int *index)
{
	char	*temp1;
	char	*temp2;
	char	*temp3;
	int		size_temp1;

	temp3 = NULL;
	printf("ANTES DE TUDO NA JOIN_STRS: str = |%s|; middle = |%s|\n", str, middle);
	printf("Vai colocar valor em temp1, chamando my_strldup. jump = %i e str[%i] = |%c|\n", jump, j, str[j]);
	temp1 = my_strldup(str, j);
	printf("temp1 = |%s|\n", temp1);
	temp2 = my_strjoin(temp1, middle);
	printf("temp2 = |%s|\n", temp2);
	size_temp1 = my_strlen(temp1);
//	printf("size_temp1 + jump = |%i|. Ou seja, str[%i] = |%c|\n", size_temp1 + jump, size_temp1 + jump, str[size_temp1 + jump]);
	printf("str: |%s| & tamanho de str: |%zu|\n", str, my_strlen(str));
	printf("size_temp1: |%i| & jump: |%i| & size_temp1 + jump: |%i|\n", size_temp1, jump, size_temp1 + jump);
	if ((int)my_strlen(str) != (size_temp1 + jump))
	{
		free(temp1);
		temp1 = fromstrldup(str, size_temp1 + jump);
		printf("temp1.2 = |%s|\n", temp1);
		temp3 = my_strjoin(temp2, temp1);
		printf("temp3 = |%s|\n", temp3);
		*index = my_strlen(temp2) - 1;
	}
	printf("Ao final de join_strs, index = %i. temp3[%i] = %c\n", *index, *index, temp3[*index]);
	free(temp1);
	free(temp2);
	return (temp3);
}

static char	*take_name_var(char *str, int j)
{
	int		i;
	int		size;
	char	*name;

	i = j;
	size = 0;
	printf("EM TAKE_NAME VAR: str[%i] == %c\n", i, str[i]);
	while (str[i] && str[i] != SPACE_CHAR)
	{
		size++;
		i++;
	}
	name = (char *)malloc((size + 1) * sizeof(char));
	size = 0;
	while (str[j] && j < i)
	{
		name[size] = str[j];
		printf("name[%i] = %c\n", size, name[size]);
		size++;
		j++;
	}
	name[size] = '\0';
	return (name);
}
