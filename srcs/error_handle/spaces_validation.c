/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:21:21 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/27 17:16:39 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char *remove_spaces(int flag, char *str, int i);
static char *add_space_after(char *s, int i);
static char	*add_space_before(char *s, int i);

extern volatile unsigned int    g_status;

int	only_spaces(char *str)
{
	int	i;
	int	size;

	i = 0;
	size = my_strlen(str);
	while (str[i])
	{
		if (str[i] == SPACE_CHAR)
			i++;
		else
			break ;
	}
	if (i == size)
	{
		g_status = NOT_FOUND;
		return (ERROR);
	}
	return (NO_ERROR);
}

char	*remove_init_and_end_spaces(char *str)
{
	int		i;

	i = 0;
	if (str[i] == SPACE_CHAR)
	{
		while(str[i] == SPACE_CHAR)
			i++;
		str = remove_spaces(1, str, i);
		i = 0;
	}
	while (str[i])
		i++;
	i--;
	if (str[i] == SPACE_CHAR)
	{
		while (i >= 0 && str[i] == SPACE_CHAR)
			i--;
		str = remove_spaces(2, str, i); 
	}
	return (str);
}

static char	*remove_spaces(int flag, char *str, int i)
{
	char	*new;

	new = NULL;
	if (flag == 1)
		new = fromstrldup(str, i - 1);
	else
		new = my_strldup(str, i + 1);
	free(str);
	str = NULL;
	return (new);
}

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
