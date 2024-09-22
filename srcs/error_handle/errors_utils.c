/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:47:55 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/21 17:44:41 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_there_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == SPACE_CHAR)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

char	*strdup_tillc(char *str)
{
	int		i;
	char	*new_str;

	new_str = NULL;
	i = 0;
//	printf("Entrou na strdup_tillc com str = %s\n", str);
	while (str[i] != SPACE_CHAR)
		i++;
//	printf("Vai dar malloc em new_str de tamanho %i\n", (i + 1));
	new_str = (char *)my_calloc((i + 1), sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[i])
	{
//		printf("Está no while em str[%i] = %c & new_str = |%s|\n", i, str[i], new_str);
		if (str[i] != SPACE_CHAR)
			new_str[i] = str[i];
		else if (str[i] == SPACE_CHAR)
			break ;
		i++;
	}
	new_str[i] = '\0';
//	printf("new_str antes de ser retornada pela strdup_tillc: %s\n", new_str);
	free(str);
	return (new_str);
}
