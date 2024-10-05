/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 22:31:08 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/18 17:18:19 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	my_echo(t_tokens *node, int fd)
{
	int			flag_nl;
	t_tokens	*temp;

	temp = node;
	flag_nl = ON;
//	printf("Entrou na função do echo\n");
	if (node == NULL)
	{
		my_putstr_fd("\n", fd);
		return (NO_ERROR);
	}
	if (strcmp(temp->word, "-n") == 0)
	{
		flag_nl = OFF;
		temp = temp->next;
	}
	while (temp)
	{
		my_putstr_fd(temp->word, fd);
		if (temp->next != NULL)
			my_putstr_fd(" ", fd);
		temp = temp->next;
	}
	if (flag_nl ==	ON)
		my_putstr_fd("\n", fd);
	return (NO_ERROR);
}
