/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 22:31:08 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/14 17:28:01 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	my_echo(t_tokens *node, int fd)
{
	int			i;
	int			size;
	int			flag_nl;
	t_tokens	*temp;

	i = 1;
	size = 0;
	temp = node;
	flag_nl = ON;
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
