/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_builtin_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 07:47:38 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/10/15 07:49:47 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_cd_error(char *str, char *err)
{
	print_error("minishell: cd: ");
	print_error(str);
	print_error(err);
}
