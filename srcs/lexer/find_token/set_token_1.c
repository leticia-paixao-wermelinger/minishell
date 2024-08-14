/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_token_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:36:37 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/08/14 14:33:33 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	is_builtin(char **s)
{
	if (my_strcmp(s[0], "echo") == 0)
		return (TRUE);
	else if (my_strcmp(s[0], "cd") == 0)
		return (TRUE);
	else if (my_strcmp(s[0], "pwd") == 0)
		return (TRUE);
	else if (my_strcmp(s[0], "export") == 0)
		return (TRUE);
	else if (my_strcmp(s[0], "unset") == 0)
		return (TRUE);
	else if (my_strcmp(s[0], "env") == 0)
		return (TRUE);
	else if (my_strcmp(s[0], "exit") == 0)
		return (TRUE);
	return (FALSE);
}
