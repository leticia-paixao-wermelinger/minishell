/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_execve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:17:35 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/03 19:36:47 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    free_matrix(char **matrix)
{
    int     i;

    i = 0;
    if (!matrix)
        return ;
    while (matrix[i])
    {
        free(matrix[i]);
        i++;
    }
    free(matrix);
}

void    execve_clean(char *path, char **args, char **env_array)
{
    free(path);
    path = NULL;
    free_matrix(args);
    free_matrix(env_array);
}
