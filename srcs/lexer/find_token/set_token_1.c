/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_token_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:36:37 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/07/26 20:47:02 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	is_builtin(char *s)
{
	if (my_strncmp(s, "echo", 4) == 0)
		return (TRUE);
	else if (my_strncmp(s, "cd", 2) == 0)
		return (TRUE);
	else if (my_strcmp(s, "pwd") == 0)
		return (TRUE);
	else if (my_strcmp(s, "export") == 0)
		return (TRUE);
	else if (my_strcmp(s, "unset") == 0)
		return (TRUE);
	else if (my_strcmp(s, "env") == 0)
		return (TRUE);
	else if (my_strcmp(s, "exit") == 0)
		return (TRUE);
	return (FALSE);
}

int	is_pipe(char *s)
{
	if (my_strcmp(s, "|") == 0)
		return (TRUE);
	return (FALSE);
}

int	is_append(char *s)
{
	if (my_strcmp(s, ">>") == 0)
		return (TRUE);
	return (FALSE);
}
