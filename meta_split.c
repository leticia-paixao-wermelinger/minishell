/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 00:17:49 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/07/01 18:54:15 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_tokens(char const *s)
{
	int	i;
	int	count;

	i = 0;
	if (!s)
		return (0);
	if (is_metachar(s[0]) == TRUE)
		count = 0;
	else
		count = 1;
	while (s[i])
	{
		if (is_metachar(s[i]) == TRUE && is_metachar(s[i + 1]) == FALSE)
			count++;
		if ((is_metachar(s[i]) == TRUE) && (s[i + 1] != '\0') && (is_metachar(s[i + 1]) == FALSE))
			count++;
		i++;
	}
	return (count);
}
/*
static char	*new_str(char const *s, int start, int end, char **vect)
{
	int		j;
	char	*str;

	j = 0;
	if (!s)
		return (0);
	str = (char *)my_calloc((end - start + 2), sizeof(char));
	if (!str)
	{
		my_clean_vect(vect);
		return (NULL);
	}
	while (start <= end)
	{
		str[j] = s[start];
		start++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

static int	verification(char const *s, char **vect)
{
	int	j;

	j = 0;
	if (!vect || !s)
		return (ERROR);
	if (s[0] == '\0')
	{
		vect[j] = NULL;
		return (ERROR);
	}
	return (NO_ERROR);
}

static char	**make_vect(char const *s, char c, char **vect, int tokens)
{
	size_t	i;
	int		j;
	int		start;

	j = 0;
	i = 0;
	start = 0;
	while (j < tokens)
	{
		if (s[i] != c && i >= 1 && s[i - 1] == c)
			start = i;
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			vect[j++] = new_str(s, start, i, vect);
		if ((i - 1) == my_strlen(s))
			break ;
		i++;
	}
	vect[j] = NULL;
	return (vect);
}
*/
char	**meta_split(char const *s)
{
	int			tokens;
	//char		**vect;

	tokens = count_tokens(s);
	my_printf("Tokens: %i\n", tokens);
	/*vect = (char **)my_calloc((tokens + 1), sizeof(char *));
	if (verification(s, vect) == ERROR)
		return (NULL);
	return (make_vect(s, vect, tokens));*/
	return (NULL);
}

/*
#include <stdio.h>

int	main()
{
	int	j = 0;
	int i = 0;
//	char *str = "    Leticia    Paixao  Wermelinger ";
//	char *str = "(null)";
//	char *str = "lorem ipsum dolor sit amet,  \
//consectetur adipiscing elit. Sed non risus.  \
//Suspendisse"; // Teste 02 do war machine
	char *str = "lorem ipsum dolor sit amet,  \
consectetur adipiscing elit. Sed non risus.  \
Suspendisse lectus tortor, dignissim sit amet,  \
adipiscing nec, ultricies sed, dolor. Cras elementum  \
ultricies diam. Maecenas ligula massa, varius a, \
semper congue, euismod non, mi.";
	char sep = 'z';
	char	**vect;

	vect = meta_split(str);	
	while (vect[i])
		i++;
	while (j <= i)
	{
		printf("|%s|\n", vect[j]);
		j++;
	}
//	printf("\n");
	j = 0;
	while (vect[j])
	{
		free(vect[j]);
		j++;
	}
	free(vect);
	return (0);
}*/
