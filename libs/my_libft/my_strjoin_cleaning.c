/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_strjoin_cleaning.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 01:55:02 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/10/15 00:31:54 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*my_join(char *s1, char *s2, char *string);

char	*my_strjoin_cleaning(char *s1, char *s2)
{
	char	*string;

	if (!s2)
		return (NULL);
	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char));
		s1[0] = '\0';
	}
	string = (char *)my_calloc((gnl_ft_strlen(s1) + gnl_ft_strlen(s2) + 1),
			sizeof(char));
	if (!string)
		return (NULL);
	string = my_join(s1, s2, string);
	free(s1);
	return (string);
}

static char	*my_join(char *s1, char *s2, char *string)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		string[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		string[i] = s2[j];
		i++;
		j++;
	}
	string[i] = '\0';
	return (string);
}
