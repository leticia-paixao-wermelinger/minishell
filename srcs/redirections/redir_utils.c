/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 09:16:50 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/24 11:40:03 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_permissions(char *pathname, int flag)
{
	if (access(pathname, flag) < 0)
	{
		permission_denied(pathname);
		return (ERROR);
	}
	return (NO_ERROR);
}
