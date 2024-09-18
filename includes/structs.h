/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:19:13 by lraggio           #+#    #+#             */
/*   Updated: 2024/09/18 17:28:19 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "enums.h"
# include "unistd.h"

typedef struct s_env	t_env;
typedef struct s_tokens	t_tokens;
typedef struct s_node	t_node;

typedef struct s_env
{
	char	*key;
	char	*value;
	t_env	*next;
}	t_env;

typedef struct s_tokens
{
	char			*word;
	enum e_token	type;
	t_tokens		*next;
}	t_tokens;

typedef struct s_node
{
	t_tokens	*token;
	int			fd_in;
	int			fd_out;
	pid_t		pid;
	int			exit_status;
	t_node		*next;
}	t_node;

typedef struct s_command
{
	char	*input;
	char	**input_matrix;
	char	*invalid_metas;
	char	*prompt;
	t_node	*l_input;
	t_env	*my_env;
}	t_command;

#endif
