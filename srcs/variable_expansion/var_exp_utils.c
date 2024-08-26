/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_exp_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:29:59 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/08/26 00:51:54 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern unsigned int   g_status;

int	print_global_var(t_node *list, char **str, int i, int j)
{
	char	*number;
	char	*temp;
	int		index;

	number = my_itoa(g_status);
	index = my_strlen(number);
	temp = join_strs(str[i], number, (j - 1), 1, &index);
	free(list->value[i]);
	list->value[i] = my_strdup(temp); 
	free(temp);
	free(number);
	printf("Ao final de print_global_var, index = %i, list->value[index] = %c\n", index, list->value[i][index]);
	return (index);
}

char	*join_strs(char *str, char *middle, int j, int jump, int *index)
{
	char	*temp1;
	char	*temp2;
	char	*temp3;
	int		size_temp1;

	printf("ANTES DE TUDO NA JOIN_STRS: str = |%s|; middle = |%s|\n", str, middle);
	printf("Vai colocar valor em temp1, chamando my_strldup. str[j] = |%c|\n", str[j]);
	temp1 = my_strldup(str, j);
	printf("temp1 = |%s|\n", temp1);
	temp2 = my_strjoin(temp1, middle);
	printf("temp2 = |%s|\n", temp2);
	size_temp1 = my_strlen(temp1);
	printf("size_temp1 + jump = |%i|. Ou seja, str[%i] = |%c|\n", size_temp1 + jump, size_temp1 + jump, str[size_temp1 + jump]);
	free(temp1);
	temp1 = fromstrldup(str, size_temp1 + jump);
	printf("temp1.2 = |%s|\n", temp1);
	temp3 = my_strjoin(temp2, temp1);
	printf("temp3 = |%s|\n", temp3);
	*index = my_strlen(temp2) - 1;
	printf("Ao final de join_strs, index = %i. temp3[%i] = %c\n", *index, *index, temp3[*index]);
	free(temp1);
	free(temp2);
	return (temp3);
}
