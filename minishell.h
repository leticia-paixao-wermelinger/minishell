/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:05:26 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/08/14 16:56:39 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libs/my_libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>

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

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_node
{
	char			**value; //ls    |     ECHO ------- TRANSFORMAR EM UMA MATRIZ
	int				token;  // e_token  
	struct s_node	*next;
}	t_node;

typedef struct s_command
{
	char	*input;
	char	**input_matrix; // 
	char	*invalid_metas;
	char	*prompt;
	t_node	*l_input;
	t_env	*my_env;
}	t_command;

char	*make_prompt(void);
void	get_env(t_command *command);
t_env	*create_first_env_node(char *c, t_env *list);
t_env	*create_last_env_node(char  *c, t_env *temp);
void	set_command(t_command *command);
void	print_env(t_env *list);
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
t_env	*my_getenv_by_list(const char *name, t_env *my_env);
int		run_commands(t_command *command);
void	make_list_from_input(t_command *command);
t_node	*create_first_input_node(char *s, t_node *list);
t_node	*create_last_input_node(char *s, t_node *prev);

// is?
int		is_pipe(char c);
int 	is_simple_quote(char c);
int 	is_double_quote(char c);
int		is_append(char *s);
int		is_redir_out(char *s);
int		is_redir_in(char *s);
int		is_heredoc(char *s);
int		is_file(t_node *node, t_node *list);
int		is_redirect(int n);
int		is_valid_exp_char(char c);
//int		is_char(char *s, char c);

// list
void	remove_env(t_env *node, t_env *start);
void	change_env_value(t_env *node, char *str);
void	create_new_ev(char *str, t_env *env_list);

// lexer
void	lexer(t_command *command);
void	set_token(t_node *node, t_node *first);
int		is_builtin(char **s);
//int		is_exec(char *s);
char    **tokenize_sentence(char *input);

// Built In
int		run_builtin(t_command *command, t_node *node);
int		pwd(t_command *command);
void	my_export(t_env *env, t_node *node_i);
void	print_env_for_export(t_env *list);
void    my_unset(t_env *env, t_node *node_i);
int		check_export_error(char **str);
char	*validate_quot_marks_for_export(char *str);

// Clear
void	clear_input(t_command *command);
void    final_clear(t_command *command);
void	free_list(t_node *list);
void	clear_loop_end(t_command *command);
void	free_env(t_env *list);

// signals
void	signal_handle(int sig);
void	setup_signal_handling(void);
void	handle_sig_error(int sig);

// Teste:

void	printlist(t_node *list);
#endif
