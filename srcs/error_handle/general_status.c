/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:47:34 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/27 21:49:13 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_status(int number)
{
	static int	g_status = 0;

	if (number >= 0)
		g_status = number;
	return (g_status);
}
