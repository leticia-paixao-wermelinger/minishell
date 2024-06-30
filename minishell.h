/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:05:26 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/06/29 18:06:35 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libs/my_libft/libft.h"
# include "libs/listlib/listlib.h"
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>

enum e_flag {
	OFF = 0,
	ON = 1
};

enum e_ascii {
	DOUBLE_QUOT_MARK = 34,
	SIMPLE_QUOT_MARK = 39,
	PIPE = 124,
	UNPRINT_CHAR = 8
};

typedef struct s_node
{
	char			*key;
	char			*value;
	struct s_node	*next;
}	t_node;


typedef struct s_command
{
	char	*input;
	char	*prompt;
	t_node	*my_env;
}	t_command;

char	*make_prompt(void);
void	copy_env(t_command *command);
t_node	*create_first_node(char *c, t_node *list);
t_node	*create_last_node(char  *c, t_node *temp);
void	set_command(t_command *command);
void	print_env(t_node *list);
void	free_list(t_node *list);
void	input_parser(t_command *command);
void	search_invalid_pipes(t_command *command);
char	*my_getenv_by_list(const char *name, t_node *my_env);
int		check_inputs(t_command *command);
#endif
