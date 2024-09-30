/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:47:34 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/30 00:44:46 by lraggio          ###   ########.fr       */
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
