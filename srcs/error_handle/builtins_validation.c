/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 07:42:14 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/10/15 07:45:32 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
* For cd...
*/

int	validate_args(t_tokens *node)
{
	if (node && node->next != NULL)
	{
		print_cd_error("", ": too many arguments\n");
		return (ERROR);
	}
	return (NO_ERROR);
}
