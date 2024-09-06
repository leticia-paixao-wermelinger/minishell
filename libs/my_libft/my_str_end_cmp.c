/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_str_end_cmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 00:18:26 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/06 16:57:29 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>


int	my_str_end_cmp(const char *s1, const char *s2)
{
	int	c1;
	int	c2;
	int	cmp;

	c1 = (int)my_strlen(s1) - 1;
	c2 = (int)my_strlen(s2) - 1;
	cmp = 0;
	while ((c1 >= 0) && (c2 >= 0) && (s1[c1]) && (s2[c2]))
	{
		cmp = (unsigned char)s1[c1] - (unsigned char)s2[c2];
		if (s1[c1] != s2[c2])
			return (cmp);
		c1--;
		c2--;
	}
	return (cmp);
}
/*
#include <string.h>
#include <stdio.h>

int	main()
{
	char	str1[] = "teste";
	char	str2[] = "testee";
	int	dif;

	dif = my_str_end_cmp(str1, str2);
	printf("%i\n", dif);

	printf("Minha função: %i \n", my_str_end_cmp(str1, str2));
	printf("Função original: %i, \n", strcmp(str1, str2));
}

Compilar: cc -Wall -Wextra -Werror -g my_str_end_cmp.c my_strlen.c && valgrind --leak-check=full --show-leak-kinds=all ./a.out
*/
