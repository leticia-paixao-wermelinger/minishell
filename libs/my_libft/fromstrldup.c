/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fromstrldup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:27:06 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/07/30 23:29:10 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

static size_t	strcopyfromc(char *dst, const char *src, int start)
{
	unsigned int	i;

	i = 0;
	while (src[start])
	{
		dst[i] = src[start];
		start++;
		i++;
	}
	dst[i] = '\0';
	return (i);
}

char	*fromstrldup(const char *s, int i)
{
	char	*dest;
	int		size;
	int		j;

	size = 0;
	j = i;
	while (s[j++])
		size++;
	dest = (char *)malloc((size + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	strcopyfromc(dest, s, (i + 1));
	return (dest);
}
/*
#include <stdio.h>

int	main()
{
	#include <string.h>

	const char	str[] = "Abacaxi";
	char	*dest2;

	dest2 = fromstrcdup(str, 'c');
	printf("fromstrcdup(): %s\n", dest2);
	free(dest2);
	return (0);
}*/
