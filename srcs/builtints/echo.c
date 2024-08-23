/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 22:31:08 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/08/22 22:44:29 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	my_echo(t_node *node, int fd)
{
	int	i;
	int	size;

	i = 1;
	size = 0;
	while (node->value[size])
		size++;
	while (node->value[i])
	{
		my_putstr_fd(node->value[i], fd);
		if (i < (size - 1))
			my_putstr_fd(" ", fd);
		i++;
	}
	my_putstr_fd("\n", fd);
	return (NO_ERROR);
}
