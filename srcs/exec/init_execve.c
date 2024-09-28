/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:07:06 by lraggio           #+#    #+#             */
/*   Updated: 2024/09/27 21:52:06 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char    *get_executable_path(t_command *command, t_node *node)
{
    t_env   *get_path;
    char    *path;
    char    **dir;
    char    *absolute_path;
    int     i;

    i = 0;
    get_path = my_getenv_by_list("PATH", command->my_env);
    path = get_path->value;
    if (!path || !get_path->value)
        return (print_error("PATH variable is unset or incorrectly set\n"), g_status(127), NULL);
    dir = my_split(path, ':');
    if (!dir)
        return (NULL);
    while (dir[i])
    {
        absolute_path = my_strjoin(dir[i], "/");
        absolute_path = my_strjoin(absolute_path, node->token->word);
        if (access(absolute_path, X_OK) == 0)
            return (free_matrix(dir), absolute_path);
        free(absolute_path);
        i++;
    }
    return (print_error("Command not found\n"), g_status(127), free_matrix(dir), NULL);
}

char    **cmd_list_to_array(t_node *sentences)
{
    int         i; //iterador p/ atribuir a matriz
    int         cmd_list_size; //quantidade de tokens na linked list dos nós
    char        **args;
    t_tokens    *current_token;

    i = 0;
    cmd_list_size = count_tokens_in_node(sentences);
    args = malloc(sizeof(char *) * (cmd_list_size + 1));
    if (!args)
        return(perror("Erro: alocação de cmd_list_to_array"), NULL);
    while (sentences)
    {
        current_token = sentences->token;
        while (current_token)
        {
            args[i] = my_strdup(current_token->word);
            if (!args[i])
            {
                free_matrix(args);
                return(perror("Erro: alocação de token em args"), NULL);
            }
            i++;
            current_token = current_token->next;
        }
        sentences = sentences->next;
    }
    args[i] = NULL;
    return (args);
}

char    **envp_list_to_array(t_env *env_list)
{
    int         i; //quantidade de args
    char        **array;

    if (!env_list)
        return (NULL);
    i = env_list_size(env_list);
    array = malloc(sizeof(char *) * (i + 1));
    if (!array)
        return (perror("Erro: alocação de envp_list_to_array"), NULL);
    i = 0;
    while(env_list) // "KEY=VALUE"
    {
        array[i] = my_strjoin(env_list->key, "=");
        array[i] = my_strjoin(array[i], env_list->value);
        env_list = env_list->next;
        i++;
    }
    array[i] = NULL;
    return (array);
}
