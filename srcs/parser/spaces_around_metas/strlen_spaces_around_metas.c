/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen_spaces_around_metas.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:59:20 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/07/21 17:39:19 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	strlen_without_spaces_post_metachars(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (is_metachar(s[i]) == TRUE)
		{
			i++;
			count++;
			while (s[i] == SPACE_CHAR)
				i++;
		}
		count++;
		i++;
	}
	return (count);
}

int	strlen_without_spaces_before_metachars(char *s)
{
	int	i;
	int	count;

	i = my_strlen(s);
	count = 0;
//	my_printf("\033[0;31mstrlen_without_spaces_before_metachars:\n");
//	my_printf("Tamanho: %i\n", i);
	i--;
	while (i >= 0)
	{
//		my_printf("s[%i] = %c\n", i, s[i]);
		if (is_metachar(s[i]) == TRUE)
		{
			i--;
			count++;
			while ((i >= 0) && (s[i] == SPACE_CHAR))
				i--;
		}
		else
		{
			count++;
			i--;
		}
	}
//	my_printf("Saiu do while c/ i = %i e count = %i\n", i, count);
	return (count);
}
