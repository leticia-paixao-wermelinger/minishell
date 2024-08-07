/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:05:26 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/07/30 21:27:10 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libs/my_libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>

enum e_flag {
	FALSE = 0,
	TRUE = 1,
	OFF = 2,
	ON = 3
};

enum e_error {
	ERROR = -1,
	NO_ERROR = 1,
	CLOSE
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

enum e_token {
	NO_INFO = 0,
	BUILTIN = 1,
	EXEC = 2,
	T_PIPE = 124, // |
	REDIR_APPEND = 3, // >>
	REDIR_OUT = 62, // >
	REDIR_IN = 60, // <
	REDIR_HEREDOC = 4, // <<
	MY_FILE = 5
};

typedef struct s_node
{
	char			*key;
	char			*value; //ls    |     ECHO
	int				token;  // e_token  
	struct s_node	*next;
}	t_node;


typedef struct s_command
{
	char	*input;
	char	**input_matrix;
	char	*invalid_metas;
	char	*prompt;
	t_node	*l_input;
	t_node	*my_env;
}	t_command;

char	*make_prompt(void);
void	get_env(t_command *command);
t_node	*create_first_env_node(char *c, t_node *list);
t_node	*create_last_env_node(char  *c, t_node *temp);
void	set_command(t_command *command);
void	print_env(t_node *list);
void	input_parser(t_command *command);
void	change_invalid_metachars(t_command *command);
int		is_metachar(char c);
void	malloc_str_of_invalid_metas(t_command *command);
char	*check_invalid_successive_metachars(char *input);
void	add_meta_to_metastring(t_command *command, int i);
char	*remove_spaces_around_metachars(char *s);
void	remove_spaces_after_metachars(char *s, char *str);
void	remove_spaces_before_metachars(char *s, char *str, int final_size);
char	**meta_split(char const *s);
int		strlen_without_spaces_post_metachars(char *s);
int		strlen_without_spaces_before_metachars(char *s);
char	**return_invalid_metas(t_command *command, char **matrix);
void	return_added_unprinted_chars(char *s, char *metas);
t_node	*my_getenv_by_list(const char *name, t_node *my_env);
int		run_commands(t_command *command);
void	make_list_from_input(t_command *command);
t_node	*create_first_input_node(char *s, t_node *list);
t_node	*create_last_input_node(char *s, t_node *prev);

// list
void	remove_node(t_node *node, t_node *start);
void	change_value(t_node *node, char *str);
void	create_new_ev(char *str, t_node *env_list);

// lexer
void	lexer(t_command *command);
void	set_token(t_node *node, t_node *first);
int		is_builtin(char *s);
//int		is_exec(char *s);
int		is_pipe(char *s);
int		is_append(char *s);
int		is_redir_out(char *s);
int		is_redir_in(char *s);
int		is_heredoc(char *s);
int		is_file(t_node *node, t_node *list);
int		is_redirect(int n);

// Built In
int		run_builtin(t_command *command, t_node *node);
int		pwd(t_command *command);
void	my_export(char **str, t_command *command);
void	print_env_for_export(t_node *list);
void	my_unset(char *name, t_command *command);
int		check_export_error(char **str);
char	*validate_quot_marks_for_export(char *str);

// Clear
void	clear_input(t_command *command);
void    clear_all(t_command *command);
void	free_list(t_node *list);

// Teste:

void	printlist(t_node *list);
#endif
