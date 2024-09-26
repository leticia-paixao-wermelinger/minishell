/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:21:21 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/26 00:33:54 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char *add_space_after(char *s, int i);
static char	*add_space_before(char *s, int i);

char	*fix_lack_of_spaces(char *str)
{
	int			i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == REDIR_OUT || str[i] == REDIR_IN)
		{
			if (str[i + 1] != SPACE_CHAR && str[i + 1] != str[i] && str[i + 1] != '\0')
				str = add_space_after(str, i);
		}
	}
	while (--i > 0)
	{
		if (str[i] == REDIR_OUT || str[i] == REDIR_IN)
		{
			if (str[i - 1] != SPACE_CHAR && str[i - 1] != str[i] && str[i - 1] != '\0')
				str = add_space_before(str, i);
		}
	}
	return (str);
}

static char	*add_space_after(char *s, int i)
{
	char	*first;
	char	*seccond;
	char	*last;
	char	*temp;

	first = my_strldup(s, i + 1);
	seccond = my_calloc(2, sizeof(char));
	seccond[0] = ' ';
	seccond[1] = '\0';
	last = fromstrldup(s, i);
	temp = my_strjoin(first, seccond);
	free(first);
	free(seccond);
	free(s);
	s = my_strjoin(temp, last);
	free(temp);
	free(last);
	return (s);
}

static char	*add_space_before(char *s, int i)
{
	char	*first;
	char	*seccond;
	char	*last;
	char	*temp;

	first = my_strldup(s, i);
	seccond = my_calloc(2, sizeof(char));
	seccond[0] = ' ';
	seccond[1] = '\0';
	last = fromstrldup(s, i - 1);
	temp = my_strjoin(first, seccond);
	free(first);
	free(seccond);
	free(s);
	s = my_strjoin(temp, last);
	free(temp);
	free(last);
	return (s);
}
