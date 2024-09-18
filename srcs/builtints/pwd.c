/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 20:42:53 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/18 17:18:19 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int pwd(void)
{
	char    cwd[1824];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (ERROR);
	printf("%s\n", cwd);
	return (NO_ERROR);
}


/*

Eu havia feito a pwd pegando o valor de env, mas descobri que o pwd no bash
continua funcionando se dermos unset no pwd, então tem que ser de outra forma.

int	pwd(t_env *env)
{
	t_env	*node;

	node = my_getenv_by_list("PWD", env);
	if (!node)
		return (ERROR);
	printf("%s\n", node->value);
	return (NO_ERROR);
}*/
