/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:07:06 by lraggio           #+#    #+#             */
/*   Updated: 2024/09/30 00:27:50 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern volatile unsigned int	g_status;

char    *get_executable_path(t_command *command, t_node *node)
{
    t_env   *get_path;
    char    *path;
    char    **dir;
    char    *temp;
    char    *absolute_path;
    int     i;

    i = 0;
    get_path = my_getenv_by_list("PATH", command->my_env);
    path = get_path->value;
    if (!(path) || !(get_path->value))
        return (print_error("PATH variable is unset or incorrectly set\n"), NULL);
    dir = my_split(path, ':');
    if (!dir)
        return (NULL);
    while (dir[i])
    {
        temp = my_strjoin(dir[i], "/");
        absolute_path = my_strjoin(temp, node->token->word);
        free(temp);
        if (access(absolute_path, F_OK | X_OK) == 0)
            return (free_matrix(dir), absolute_path);
        free(absolute_path);
        i++;
    }
    return (print_cmd_not_found(node), free_matrix(dir), NULL);
}

char    **cmd_list_to_array(t_node *sentences)
{
    int         i;
    int         cmd_list_size;
    char        **args;
    t_tokens    *current_token;

    i = 0;
    cmd_list_size = count_tokens_in_node(sentences);
    args = malloc(sizeof(char *) * (cmd_list_size + 1));
    if (!args)
        return(print_error("Erro: alocação de cmd_list_to_array"), NULL);
    if (sentences)
    {
        current_token = sentences->token;
        while (current_token)
        {
            args[i] = my_strdup(current_token->word);
            if (!args[i])
                return(free_matrix(args), NULL);
            i++;
            current_token = current_token->next;
        }
    }
    args[i] = NULL;
    return (args);
}

char    **envp_list_to_array(t_env *env_list)
{
    int         i;
    char        **array;
    char        *temp;

    if (!env_list)
        return (NULL);
    i = env_list_size(env_list);
    array = malloc(sizeof(char *) * (i + 1));
    if (!array)
        return (NULL);
    i = 0;
    while(env_list) // "KEY=VALUE"
    {
        temp = my_strjoin(env_list->key, "=");
        array[i] = my_strjoin(temp, env_list->value);
        free(temp);
        if (!array[i])
            return (free_matrix(array), NULL);
        env_list = env_list->next;
        i++;
    }
    array[i] = NULL;
    return (array);
}
