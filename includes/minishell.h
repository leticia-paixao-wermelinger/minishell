
#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/my_libft/libft.h"
# include "enums.h"
# include "structs.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

//------------------MAIN------------------
// main.c
int			main(int argc, char *argv[]);
void		exec_and_clear(t_command command);
// prompt_and_inputs.c
void		set_command(t_command *command);
char		*make_prompt(void);
// pre_exec.c
int			pre_exec(t_command *command);

//------------------PARSER------------------
// parser.c
int			parser(t_command *command);
char		**split_sentence_by_char(char *input, char c);
char		**tokenize_sentence(char *input);
// tokenize_words.c
void		search_tokens(t_node *input);
void		set_token(t_tokens *token, int command, int count);
int			is_builtin(char *s);
// LINKED_LIST_INPUT
// create_list_input.c
t_tokens	*make_list_tokens(char *s, t_node *list);
void		make_list_from_input(t_command *command);
void		free_sentences(char **sentences);
void		free_tokens(t_tokens *token);

//------------------ERROR_HANDLE------------------
// input_validation.c
int			first_input_validation(t_command *command);
int			general_input_validation(t_node *node);
// pipe_and_redir_validation.c
int			check_pipes_with_redir(char *str);
// pipe_validation.c
int			check_pipe_init_and_end(char *str);
int			check_double_pipe_together(char **str);
int			check_following_pipes(char *str);
char		*remove_after_double_pipe(char **str, int i);
// print_syntax_error.c
int			pipe_syntax_error(int flag);
int			redir_syntax_error(enum e_token e);
// print_general_error.c
void		print_error(char *str);
int			no_such_file(char *str);
int			permission_denied(char *str);
void		print_no_such_file(char **argv);
void		print_heredoc_ctrld(int count, char *delimiter);
// print_builtin_error.c
void		print_cd_error(char *str, char *err);
// quote_validation.c
int			n_quote_validation(char *str, enum e_flag double_quote,
				enum e_flag simple_quote);
int			dollar_is_closed_by_quote(char **str, int index_dollar, int quote);
// meta_closed_quote_validation.c
void		remove_closed_in_quotes_metas(char *str, enum e_flag double_quote,
				enum e_flag single_quote);
void		return_closed_in_quotes_metas(char *str);
// single_quote_validation.c
void		single_quotes_to_unprintable(t_node *list);
// redir_validation.c
int			input_ends_with_redir(char *str);
int			check_following_redirs(t_tokens *node);
// remove_quotes.c
void		remove_all_quotes(t_node *list, int quote);
void		remove_quote(char **str, int i, enum e_ascii quote);
// errors_utils.c
int			is_there_space(char *str);
char		*strdup_tillc(char *str);
int			is_empty(char *str);
// spaces_validation.c
int			only_spaces(char *str);
char		*remove_init_and_end_spaces(char *str);
// spaces_validation_2.c
char		*fix_lack_of_spaces(char *s);
// general_status.c
int			g_status(int number);
// builtins_validation.c
int			validate_args(t_tokens *node);

//----------------GENERAL_FUNCTIONS------------------
// is_chars_functions.c
int			is_pipe(char c);
int			is_simple_quote(char c);
int			is_double_quote(char c);
int			is_append(char *s);
int			is_valid_exp_char(char c);
// is_chars_functions_2.c
int			is_redir_out(char *s);
int			is_redir_in(char *s);
int			is_heredoc(char *s);
int			is_redirect(char *str);
int			token_is_redir(t_tokens *node);
// is_chars_functions_3.c
int			is_char(char o, char c);

//---------------------SIGNALS---------------------
// signal_handle.c
void		signal_handle(int sig);
void		setup_heredoc_signal_handling(void);
void		setup_signal_handling(void);
void		heredoc_signal_handle(int sig);

//-----------------LINKED_LIST---------------------
// change_list.c
void		remove_env(t_env *node, t_env *start);
void		remove_first_word_token(t_tokens *start, t_node *sentence);
void		remove_word_token(t_tokens *node, t_tokens *start,
				t_node *sentence);
void		remove_empty_nodes(t_node *main_node);
// list_functions.c
void		create_first_input_token(char *word, t_tokens *list);
t_env		*create_first_env_node(char *c, t_env *list);
t_env		*create_last_env_node(char *c, t_env *temp);
t_node		*create_first_input_node(char *s, t_node *list);
t_node		*create_last_input_node(char *s, t_node *prev);
// list_functions_2.c
t_tokens	*create_last_token(char *word, t_tokens *prev);
//                  Teste:
void		printlist(t_node *list);
void		print_tokens(t_tokens *token);
// heredoc_list.c
t_tokens	*create_heredoc_list(char *str);

//-----------------VARIABLE_EXPANSION---------------------
// var_exp.c
void		var_exp(t_command *command);
void		search_dollar(t_tokens *node_token, t_env *env);
int			check_post_dollar(t_tokens *token, char *str, int j, t_env *env);
// var_exp_utils.c
int			print_global_var(t_tokens *token, char *str, int j);
int			double_dollar(t_tokens *token, char *str, int j);
int			expand_variable(t_tokens *token, t_env *env, char *str, int j);
char		*join_strs(char *str, char *middle, int *arr, int *index);
// var_exp_utils_2.c
char		*take_name_var(char *str, int j);
// heredoc_exp.c
char		*expand_heredoc_variables(char *str, t_env *env);

//---------------------------ENV-----------------------
// env_utils.c
void		get_env(t_command *command);
t_env		*my_getenv_by_list(const char *name, t_env *my_env);

//--------------------REDIRECTIONS--------------------
// find_redir.c
int			redirections(t_node *sentence, t_command *command, int ret,
				int flag_first);
int			find_heredoc(t_node *sentence);
// do_redir.c
int			do_heredoc(t_node *sentence, t_tokens *redir_node,
				t_command *command);
int			do_append(t_node *sentence, t_tokens *redir_node);
int			do_redir_out(t_node *sentence, t_tokens *redir_node);
int			do_redir_in(t_node *sentence, t_tokens *word);
// heredoc_utils.c
void		heredoc_child_process(int *fds, t_tokens *redir_node,
				t_command *command);
// redir_utils.c
int			check_permissions(char *pathname, int flag);
void		remove_redir_nodes(t_node *sentence, t_tokens *redir_node);

//---------------------EXEC-----------------------
// GENERAL
// check_cmds.c
int			check_cmds(t_node *sentence);
int			is_valid_cmd(t_node *sentence);
// executor.c
int			executor(t_command *command, t_node *sentence);
void		execute_cmds(t_command *command, t_node *sentence, int has_pipe);
void		run_simple_commands(t_command *command, t_node *node);
void		update_status(t_node *sentence);
void		wait_cmds(t_node *node);
// print_exec_error.c
void		print_errno(t_node *node);
// utils.c
int			node_list_size(t_node *node);
void		close_all_node_fds(t_node *node);
void		close_node_fds(t_node *node);
void		do_dup2(t_node *node);
// PIPE
// make_pipe.c
int			has_pipe_or_not(t_node *sentence);
int			pipe_config(t_node *node);
void		make_pipe(t_node *sentence);
// void	print_fds(t_node *node);
// pipe_execution.c
int			pipe_execution(t_command *command, t_node *node);
int			run_pipe_builtin(t_command *command, t_tokens *token, t_env *env,
				int fd);
void		check_next_node(t_node *node);
void		run_pipe_execve(t_command *command, t_node *list);
char		*check_path(t_command *cmd, t_node *node, char **env_array);
// EXECVE
// clean_execve.c
void		execve_clean(char **args, char **env_array);
void		free_matrix(char **matrix);
// execve_utils.c
int			env_list_size(t_env *list);
int			count_tokens_in_node(t_node *sentence);
// init_execve.c
char		**envp_list_to_array(t_env *env_list);
char		**cmd_list_to_array(t_node *sentences);
char		*get_executable_path(t_command *command, t_node *list);
// run_execve.c
void		run_execve(t_command *command, t_node *list);

//------------------------BUILTINS-----------------------
// builtins.c
int			run_builtin(t_command *command, t_node *node, t_env *env, int fd);
// cd.c
int			my_cd(t_tokens *node, t_env *env);
// echo.c
int			my_echo(t_tokens *node, int fd);
// exit.c
int			my_exit(t_tokens *token, t_command *command);
// pwd.c
int			pwd(void);
// ENV
// env_bt_utils.c
void		print_env_for_export(t_env *list, int fd);
void		change_env_value(t_env *env, char *str);
void		create_new_ev(char *str, t_env *env);
int			is_valid_ev(char *str);
// env_builtins.c
void		print_env(t_env *list, int fd);
void		my_export(t_env *env, t_tokens *node_t, int fd);
void		my_unset(t_env *env, t_tokens *node_i);

//------------------------CLEANING-----------------------
// clear_loop.c
void		clear_loop_end(t_command *command);
void		clear_input(t_command *command);
void		final_clear(t_command *command);
// clear_funct.c
void		free_list(t_node *list);
void		free_t_tokens(t_tokens *node);
void		free_env(t_env *list);

#endif
