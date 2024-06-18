/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 00:17:49 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/02/17 00:17:52 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	if (!s)
		return (0);
	if (s[0] == c)
		count = 0;
	else if (c == '\0')
	{
		count = 1;
		return (count);
	}
	else
		count = 1;
	while (s[i])
	{
		if ((s[i] == c) && (s[i + 1] != '\0') && (s[i + 1] != c))
			count++;
		i++;
	}
	return (count);
}

static char	*new_str(char const *s, int start, int end)
{
	int		j;
	char	*str;

	j = 0;
	if (!s)
		return (0);
	str = (char *)my_calloc((end - start + 2), sizeof(char));
	if (!str)
		return (NULL);
	while (start <= end)
	{
		str[j] = s[start];
		start++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

static int	verification(char const *s, char c, char **vect)
{
	int	j;

	j = 0;
	if (!vect || !s)
		return (0);
	if (s[0] == '\0')
	{
		vect[j] = NULL;
		return (1);
	}
	if (c == '\0')
	{
		vect[j] = new_str(s, 0, my_strlen(s));
		vect[j + 1] = NULL;
		return (1);
	}
	return (2);
}

static char	**make_vect(char const *s, char c, char **vect, int count)
{
	size_t	i;
	int		j;
	int		start;

	j = 0;
	i = 0;
	start = 0;
	while (j < count)
	{
		if (s[i] != c && i >= 1 && s[i - 1] == c)
			start = i;
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			vect[j++] = new_str(s, start, i);
		if ((i - 1) == my_strlen(s))
			break ;
		i++;
	}
	vect[j] = NULL;
	return (vect);
}

char	**my_split(char const *s, char c)
{
	int		count;
	char	**vect;

	count = count_words(s, c);
	vect = (char **)my_calloc((count + 1), sizeof(char *));
	if (verification(s, c, vect) == 0)
		return (NULL);
	if (verification(s, c, vect) == 1)
		return (vect);
	return (make_vect(s, c, vect, count));
}
