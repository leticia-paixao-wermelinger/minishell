/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 13:52:16 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/08/11 01:20:48 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	my_cd(char *path)
{
	if (chdir(path) != 0)
	{
		//ERROR
		//print_error
		//return (ERROR);
	}
	//change path of env
	//change oldpwd of env
		return (NO_ERROR);
}
