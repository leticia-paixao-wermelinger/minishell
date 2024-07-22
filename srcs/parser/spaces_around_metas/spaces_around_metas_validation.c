/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces_around_metas_validation.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:54:41 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/07/21 23:55:49 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*remove_spaces_around_metachars(char *s)
{
	int		new_size;
	char	*str;

//	printf("\033[0;32mEm remove_spaces_around_metachars:\n");
	new_size = strlen_without_spaces_post_metachars(s);
	str = (char *)malloc((new_size + 1) * sizeof(char));
//	printf("ANTES DE REMOVE_SPACES_AFTER: s == %s\n", s);
//	printf("ANTES DE REMOVE_SPACES_AFTER: str(nova string) == %s\n", str);
	remove_spaces_after_metachars(s, str);
//	printf("DEPOIS DE REMOVE_SPACES_AFTER: s == %s\n", s);
//	printf("DEPOIS DE REMOVE_SPACES_AFTER: str(nova string) == %s\n", str);
	free(s);
	new_size = strlen_without_spaces_before_metachars(str);
	s = (char *)malloc((new_size + 1) * sizeof(char));
//	printf("ANTES DE REMOVE_SPACES_BEFORE: s == %s\n", s);
//	printf("ANTES DE REMOVE_SPACES_BEROFE: str(nova string) == %s\n", str);
	remove_spaces_before_metachars(str, s, new_size);
//	printf("DEPOIS DE REMOVE_SPACES_BEFORE: s == %s\n", s);
//	printf("DEPOIS DE REMOVE_SPACES_BEROFE: str(nova string) == %s\n", str);
	free(str);
	return (s);
}

void	remove_spaces_after_metachars(char *s, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		str[j] = s[i];
		j++;
		if (is_metachar(s[i]) == TRUE)
		{
			i++;
			while (s[i] == SPACE_CHAR)
				i++;
		}
		else
			i++;
	}
	str[j] = '\0';
}

void    remove_spaces_before_metachars(char *s, char *str, int final_size)
{
	int		i;
	int		j;

	i = my_strlen(s);
	j = final_size;
//	printf("\033[0;33mremove_spaces_before_metachars:\n");
//	printf("String: %s\n", s);
//	printf("Fora do while: i = %i & j = %i\n", i , j);
	str[j] = '\0';
	while (i >= 0)
	{
//		printf("Dentro do while: i = %i & j = %i\n", i , j);
		str[j] = s[i];
//		printf("str[%i] = %c & s[%i] = %c\n", j, str[j], i, s[i]);
		j--;
		if (is_metachar(s[i]) == TRUE)
		{
			i--;
			while (s[i] == SPACE_CHAR)
				i--;
		}
		else
			i--;
	}
//	printf("\033[0m");
}
