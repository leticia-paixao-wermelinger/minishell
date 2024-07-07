/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:05:26 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/07/06 22:48:57 by lpaixao-         ###   ########.fr       */
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
	ON = 1,
	TRUE = 2,
	FALSE = -1
};

enum e_error {
	ERROR = -1,
	NO_ERROR = 1
};

enum e_ascii {
	DOUBLE_QUOT_MARK = 34,	// "
	SIMPLE_QUOT_MARK = 39,	// '
	PIPE = 124,				// |
	AMPERSAND = 38,			// &
	SEMICOLON = 59,			// ;
	OPEN_PARENTHESIS = 40,	// (
	CLOSE_PARENTHESIS = 41,	// )
	LESS_THAN = 60,			// <
	GREATER_THAN = 62,		// >
	SPACE_CHAR = 32,		// space
	TAB_CHAR = 9,			// \t
	NEWLINE_CHAR = 10,		// \n
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
	char	**input_matrix;
	char	*invalid_metas;
	char	*prompt;
	t_node	*my_env;
}	t_command;

char	*make_prompt(void);
void	get_env(t_command *command);
t_node	*create_first_node(char *c, t_node *list);
t_node	*create_last_node(char  *c, t_node *temp);
void	set_command(t_command *command);
void	print_env(t_node *list);
void	free_list(t_node *list);
void	input_parser(t_command *command);
void	search_invalid_metachars(t_command *command);
int		is_metachar(char c);
void	malloc_str_of_invalid_metas(t_command *command);
void	add_meta_to_metastring(t_command *command, int i);
char	*remove_spaces_around_metachars(char *s);
void	remove_spaces_after_metachars(char *s, char *str);
void	remove_spaces_before_metachars(char *s, char *str, int final_size);
char	**meta_split(char const *s);
int		strlen_without_spaces_post_metachars(char *s);
int		strlen_without_spaces_before_metachars(char *s);
char	*my_getenv_by_list(const char *name, t_node *my_env);
int		check_inputs(t_command *command);
#endif
