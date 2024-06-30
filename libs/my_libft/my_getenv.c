/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 00:50:41 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/06/29 01:07:56 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *my_getenv_by_list(const char *name, )
{
	extern char	**environ;


}

static void	test()
{
	#include <stdlib.h>

	printf("My funct = PATH : %s\n", my_getenv_by_list("PATH"));
	printf("Or funct = PATH : %s\n", getenv("PATH"));
	
	printf("--------------------------\n");

	printf("My funct = HOME : %s\n", my_getenv_by_list("HOME"));
	printf("Or funct = HOME : %s\n", getenv("HOME"));

	printf("--------------------------\n");

	printf("My funct = ROOT : %s\n", my_getenv_by_list("ROOT"));
	printf("Or funct = ROOT : %s\n", getenv("ROOT"));
}
