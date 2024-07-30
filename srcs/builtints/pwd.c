/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 20:42:53 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/07/29 22:14:49 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	pwd(t_command *command)
{
	t_node	*node;
	node = my_getenv_by_list("PWD", command->my_env);
	if (!node)
		return (ERROR);
	printf("%s\n", node->value);
	return (NO_ERROR);
}
