/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 20:42:53 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/07/29 20:43:18 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	pwd(t_command *command)
{
	char	*path;
	path = my_getenv_by_list("PWD", command->my_env);
	if (!path)
		return (ERROR);
	printf("%s\n", path);
	return (NO_ERROR);
}
