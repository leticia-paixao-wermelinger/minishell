/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:05:26 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/27 21:28:52 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "structs.h"
# include "enums.h"
# include "../libs/my_libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <limits.h>

//------------------MAIN------------------
//main.c
int		main(int argc, char *argv[]);
//prompt_and_inputs.c
void	set_command(t_command *command);
char	*make_prompt(void);
//pre_exec.c
int		pre_exec(t_command   *command);

//------------------PARSER------------------
//parser.c
int		parser(t_command *command);
char	**split_sentence_by_char(char *input, char c);
char	**tokenize_sentence(char *input);
//tokenize_words.c
void	search_tokens(t_node *input);
void    set_token(t_tokens *token, int command, int count);
int		is_builtin(char *s);
//LINKED_LIST_INPUT
//create_list_input.c
t_tokens	*make_list_tokens(char *s, t_node *list);
void	make_list_from_input(t_command *command);
void	free_sentences(char **sentences);
void	free_tokens(t_tokens *token);

//------------------ERROR_HANDLE------------------
//input_validation.c
int		first_input_validation(t_command *command);
int		general_input_validation(t_node *node);
//pipe_and_redir_validation.c
int		check_pipes_with_redir(char *str);
//pipe_validation.c
int		check_pipe_init_and_end(char *str);
int		check_double_pipe_together(char **str);
int		check_following_pipes(char *str);
char	*remove_after_double_pipe(char **str, int i);
//print_error.c
void	print_error(char *str);
int		pipe_syntax_error(int flag);
int		redir_syntax_error(enum e_token e);
int		no_such_file(char *str);
int		permission_denied(char *str);
void	print_no_such_file(char **argv);
//quote_validation.c
int		n_quote_validation(char *str);
int		dollar_is_closed_by_single_quote(char **str);
void	remove_closed_in_quotes_metas(char *str);
void	return_closed_in_quotes_metas(char *str);
// redir_validation.c
int		input_ends_with_redir(char *str);
int		check_following_redirs(t_tokens *node);
//remove_quotes.c
void	remove_all_quotes(t_node *list, int quote);
void	remove_quote(char **str, int i, enum e_ascii quote);
//errors_utils.c
int		is_there_space(char *str);
char	*strdup_tillc(char *str);
//spaces_validation.c
int		only_spaces(char *str);
char	*remove_init_and_end_spaces(char *str);
char	*fix_lack_of_spaces(char *s);
//general_status.c
int		g_status(int number);

//----------------GENERAL_FUNCTIONS------------------
//is_chars_functions.c
int		is_pipe(char c);
int 	is_simple_quote(char c);
int 	is_double_quote(char c);
int		is_append(char *s);
int		is_valid_exp_char(char c);
//is_chars_functions_2.c
int		is_redir_out(char *s);
int		is_redir_in(char *s);
int		is_heredoc(char *s);
int		is_redirect(char *str);
int		token_is_redir(t_tokens *node);
//is_chars_functions_3.c
int		is_char(char o, char c);

//---------------------SIGNALS---------------------
//signal_handle.c
void	signal_handle(int sig);
void	setup_signal_handling(void);
void	handle_sig_error(int sig);

//-----------------LINKED_LIST---------------------
//change_list.c
void	remove_env(t_env *node, t_env *start);
void	remove_word_token(t_tokens *node, t_tokens *start);
//list_functions.c
void	create_first_input_token(char *word, t_tokens *list);
t_env	*create_first_env_node(char *c, t_env *list);
t_env	*create_last_env_node(char  *c, t_env *temp);
t_node	*create_first_input_node(char *s, t_node *list);
t_node	*create_last_input_node(char *s, t_node *prev);
t_tokens	*create_last_token(char *word, t_tokens *prev);
//                  Teste:
void	printlist(t_node *list);
void	print_tokens(t_tokens *token);
//heredoc_list.c
t_tokens	*create_heredoc_list(char *str);

//--------------------REDIRECTIONS--------------------
//find_redir.c
int		redirections(t_node *sentence, t_env *env);
int		find_heredoc(t_node *sentence);
//do_redir.c
int		do_heredoc(t_node *sentence, t_tokens *redir_node, t_env *env);
int		do_append(t_node *sentence, t_tokens *redir_node);
int		do_redir_out(t_node *sentence, t_tokens *redir_node);
int		do_redir_in(t_node *sentence, t_tokens *word);
//redir_utils.c
int		check_permissions(char *pathname, int flag);

//-----------------VARIABLE_EXPANSION---------------------
//var_exp.c
void	var_exp(t_command *command);
void	search_dollar(t_tokens *node_token, t_env *env);
int		check_post_dollar(t_tokens *token, char *str, int j, t_env *env);
//var_exp_utils.c
int		print_global_var(t_tokens *token, char *str, int j);
int		double_dollar(t_tokens *token, char *str, int j);
int		expand_variable(t_tokens *token, t_env *env, char *str, int j);
char	*join_strs(char *str, char *middle, int j, int jump, int *index);
//heredoc_exp.c
char	*expand_heredoc_variables(char *str, t_env *env);

//---------------------------ENV-----------------------
//env_utils.c
void	get_env(t_command *command);
t_env	*my_getenv_by_list(const char *name, t_env *my_env);

//---------------------EXEC-----------------------
//clean_execve.c
void	execve_clean(char *path, char **env_array, t_command *command);
void	free_matrix(char **matrix);
//executor.c
int		executor(t_command *command, t_node *sentence);
int		run_commands(t_command *command, t_node *node);
//execve_utils.c
int		env_list_size(t_env *list);
int		count_tokens_in_node(t_node *sentence);
//init_execve.c
char	**envp_list_to_array(t_env *env_list);
char	**cmd_list_to_array(t_node *sentences);
char	*get_executable_path(t_command *command, t_node *list);
//pipe_execution.c
int		pipe_execution(t_command *command, t_node *node);
//run_execve.c
int		run_execve(t_command *command, t_node *list);
//fd.c
void	close_fds(int fd_1, int fd_2);
//redirect.c

//------------------------BUILTINS-----------------------
//builtins.c
int		run_builtin(t_command *command, t_tokens *token, t_env *env, int fd);
//cd.c
int		my_cd(t_tokens *node, t_env *env);
//echo.c
int		my_echo(t_tokens *node, int fd);
//exit.c
int		my_exit(t_tokens *token, t_command *command);
//pwd.c
int		pwd(void);
//ENV
//env_bt_utils.c
void	print_env_for_export(t_env *list, int fd);
void	change_env_value(t_env *env, char *str);
void	create_new_ev(char *str, t_env *env);
int		is_valid_ev(char *str);
//env_builtins.c
void	print_env(t_env *list, int fd);
void	my_export(t_env *env, t_tokens *node_t, int fd);
void	my_unset(t_env *env, t_tokens *node_i);

//------------------------CLEANING-----------------------
//clear_funct.c
void	clear_loop_end(t_command *command);
void	clear_input(t_command *command);
void	final_clear(t_command *command);
void	free_list(t_node *list);
void	free_t_tokens(t_tokens *node);
void	free_env(t_env *list);

#endif
