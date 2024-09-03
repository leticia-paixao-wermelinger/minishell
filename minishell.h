/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:05:26 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/03 19:57:35 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

/*
Valores Padrão:
0: Sucesso. O comando foi executado com sucesso.
1: Erro Geral. Indica uma falha genérica ou um erro não específico.
Erros Comuns:
127: Comando Não Encontrado. Código retornado quando o shell não consegue encontrar o comando especificado. É uma maneira padrão de indicar que o comando não foi encontrado no caminho especificado.
Outros Valores:
2-125: Podem ser utilizados por comandos e programas para indicar erros específicos. Esses valores são definidos pelos próprios programas e podem variar.
126: Comando Não Executável. Esse código indica que o comando foi encontrado, mas não é executável (por exemplo, se não tiver permissões de execução).
128: Usado para indicar que o comando foi terminado por um sinal. O código de saída é o número do sinal adicionado a 128 (por exemplo, 128 + 2 para SIGINT).

0: Success—Indicates that the command or program executed successfully without any errors.
1: General Error—A catch-all exit code for a variety of general errors. Often used when the command or program encounters an error, but no specific exit code is available for the situation.
2: Misuse of shell built-ins—Indicates incorrect usage of shell built-in commands or misuse of shell syntax.
126: Command cannot execute—The command was found, but it could not be executed, possibly due to insufficient permissions or other issues.
127: Command not found—The command was not found in the system's PATH, indicating that either the command does not exist or the PATH variable is incorrectly set.
128: Invalid exit argument—Returned when a script exits with an invalid argument. This usually indicates an error in the script itself.
128 + N: Fatal error signal N—Indicates that the command or program was terminated by a fatal error signal. For example, an exit code of 137 (128 + 9) means that the command was terminated by a SIGKILL signal.
130: Script terminated by Control-C—Indicates that the command or script was terminated by the user using Control-C (SIGINT signal).
255: Exit status out of range—Returned when the exit status is outside the valid range (0 to 254).
*/

enum e_error {
	NO_ERROR = 0,
	ERROR = 1,
	MISUSE = 2,
	CANT_EXEC = 126,
	NOT_FOUND = 127,
	INVALID_EXIT_ARG = 128,
	FATAL_ERROR_MINUS_N = 128,
	USED_CTRL_C = 130, // DONE
	EXIT_STATUS_OUT_RANGE = 255,
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
	DOLLAR = 36,			//$
	QUESTION_MARK = 63,		//?
	SPACE_CHAR = 32,		// space
	TAB_CHAR = 9,			// \t
	NEWLINE_CHAR = 10,		// \n
	UNPRINT_CHAR = 8
};

enum e_token {
	NO_INFO = 0,
	COMMAND = 1,
	ARGUMENT = 2,
	BUILTIN = 4,
	EXEC = 5,
	T_PIPE = 124, // |
	REDIR_APPEND = 3, // >>
	REDIR_OUT = 62, // >
	REDIR_IN = 60, // <
	REDIR_HEREDOC = 6, // <<
	OUTFILE = 7,
	INFILE  = 8
};

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

char	*make_prompt(void);
void	get_env(t_command *command);
t_env	*create_first_env_node(char *c, t_env *list);
t_env	*create_last_env_node(char  *c, t_env *temp);
void	set_command(t_command *command);
void	print_env(t_env *list, int fd);
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

// parser
void	parser(t_command *command);
char	**split_sentence_by_char(char *input, char c);
//char	**split_sentences(char *input);

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
int		is_valid_ev(char *str);
int		is_char(char o, char c);
//int		is_char(char *s, char c);

// list
void	remove_env(t_env *node, t_env *start);
t_tokens    *make_list_tokens(char *s, t_node *list);
void    create_first_input_token(char *word, t_tokens *list);
t_tokens    *create_last_token(char *word, t_tokens *prev);
//void	change_env_value(t_env *node, char *str);
//void	create_new_ev(char *str, t_env *env_list);

// lexer
void	lexer(t_command *command);
void	set_token(t_node *node, t_node *first);
int		is_builtin(char **s);
//int		is_exec(char *s);
char    **tokenize_sentence(char *input);

// Built In
int		run_builtin(t_command *command, t_node *node, int fd);
int		pwd(t_command *command);
void	my_export(t_env *env, t_node *node_i, int fd);
void	print_env_for_export(t_env *list, int fd);
void    my_unset(t_env *env, t_node *node_i);
int		check_export_error(char **str);
char	*validate_quot_marks_for_export(char *str);
int		is_valid_ev(char *str);
void	change_env_value(t_env *env, char *str);
void	create_new_ev(char *str, t_env *env);
int		my_cd(t_node *node, t_env *env);
int		my_echo(t_node *node, int fd);

// Clear
void	clear_input(t_command *command);
void    final_clear(t_command *command);
void	free_list(t_node *list);
void	clear_loop_end(t_command *command);
void	free_env(t_env *list);
void	free_sentences(char **sentences);
void	free_tokens(t_tokens *token);

// signals
void	signal_handle(int sig);
void	setup_signal_handling(void);
void	handle_sig_error(int sig);

// variable expansion
void	var_exp(t_command *command);
void	search_dollar(t_node *list, t_tokens *node_token, t_env *env);
int		check_post_dollar(t_tokens *token, char *str, int j, t_env *env);
int		print_global_var(t_tokens *token, char *str, int j);
int		double_dollar(t_node *list, char **str, int i, int j);
int		expand_variable(t_node *list, t_env *env, char **str, int i, int j);
char	*join_strs(char *str, char *middle, int j, int jump, int *index);

// Teste:

void	printlist(t_node *list);
#endif
