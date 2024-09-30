/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_exp_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:29:59 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/26 09:25:12 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*take_name_var(char *str, int j);

int	print_global_var(t_tokens *token, char *str, int j)
{
	char	*number;
	char	*temp;
	int		index;

	number = my_itoa(g_status(-1));
	index = my_strlen(number);
	temp = join_strs(str, number, (j - 1), 1, &index);
	free(token->word);
	token->word = my_strdup(temp);
	free(temp);
	free(number);
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
	node = my_getenv_by_list(key, env);
	if (!node || (my_str_end_cmp(node->key, key) != 0))
	{
		temp = my_strldup(str, (j - 1));
		index = my_strlen(key) - 1;
	}
	else
	{
		temp = join_strs(str, node->value, (j - 1), (my_strlen(node->key)), &index);
		if (!temp)
		{
			free(key);
			return (ERROR);
		}
	}
	free(token->word);
	token->word = my_strdup(temp);
	free(temp);
	free(key);
	return (index);
}

char	*join_strs(char *str, char *middle, int j, int jump, int *index)
{
	char	*temp1;
	char	*temp2;
	char	*temp3;
	int		size_temp1;

	temp3 = NULL;
	temp1 = my_strldup(str, j);
	temp2 = my_strjoin(temp1, middle);
	size_temp1 = my_strlen(temp1);
	if ((int)my_strlen(str) != (size_temp1 + jump))
	{
		free(temp1);
		temp1 = fromstrldup(str, size_temp1 + jump);
		temp3 = my_strjoin(temp2, temp1);
		*index = my_strlen(temp2) - 1;
	}
	else
		temp3 = strdup(temp2);
	free(temp1);
	free(temp2);
	return (temp3);
}

/*
The following function finds and returns the name of the variable requested, in order to be compared
with the list of enviromental vars
*/

static char	*take_name_var(char *str, int j)
{
	int		i;
	int		size;
	char	*name;

	i = j;
	size = 0;
	while (str[i] && (my_isalpha(str[i]) != 0 || my_isdigit(str[i]) != 0))
	{
		size++;
		i++;
	}
	name = (char *)malloc((size + 1) * sizeof(char));
	if (!name)
		return (NULL);
	size = 0;
	while (str[j] && j < i)
	{
		name[size] = str[j];
		size++;
		j++;
	}
	name[size] = '\0';
	return (name);
}
