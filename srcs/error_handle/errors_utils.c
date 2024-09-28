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
	while (str[i] != SPACE_CHAR)
		i++;
	new_str = (char *)my_calloc((i + 1), sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] != SPACE_CHAR)
			new_str[i] = str[i];
		else if (str[i] == SPACE_CHAR)
			break ;
		i++;
	}
	new_str[i] = '\0';
	free(str);
	return (new_str);
}
