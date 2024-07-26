/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_token_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:36:37 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/07/26 20:23:59 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	is_builtin(char *s)
{
	if (my_strncmp(s, "echo", 4) == 0) // echo (-n)
	{
		printf("%s é echo\n", s);
		return (TRUE);
	}
	else if (my_strncmp(s, "cd", 2) == 0)	// cd (1 caminho)
	{
		printf("%s é cd\n", s);
		return (TRUE);
	}
	else if (my_strcmp(s, "pwd") == 0)	// pwd -NO
	{
		printf("%s é pwd\n", s);
		return (TRUE);
	}
	else if (my_strcmp(s, "export") == 0)	// export -NO
	{
		printf("%s é export\n", s);
		return (TRUE);
	}
	else if (my_strcmp(s, "unset") == 0)	// unset -NO
	{
		printf("%s é unset\n",s);
		return (TRUE);
	}
	else if (my_strcmp(s, "env") == 0)	// env -NO or arguments
	{
		printf("%s é env\n", s);
		return (TRUE);
	}
	else if (my_strcmp(s, "exit") == 0)	// exit -NO
	{
		printf("%s é exit\n", s);
		return (TRUE);
	}
	return (FALSE);
}
/*
int	is_exec(char *s)
{
	(void)s;
	return (FALSE);
}
*/
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
