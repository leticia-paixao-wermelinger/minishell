
#include "../../includes/minishell.h"

static void	heredoc_loop(int *fds, t_tokens *redir_node, t_command *command,
				t_heredoc *here_struct);
static int	handle_heredoc_input(int *fds, t_command *command,
				t_heredoc *here_struct);
static void	free_str(t_heredoc *here_struct);

void	heredoc_child_process(int *fds, t_tokens *redir_node,
		t_command *command)
{
	t_heredoc	here_struct;

	my_bzero(&here_struct, sizeof(t_heredoc));
	close(fds[0]);
	setup_heredoc_signal_handling();
	heredoc_loop(fds, redir_node, command, &here_struct);
	close(fds[1]);
	close_all_node_fds(command->l_input);
	clear_loop_end(command);
	final_clear(command);
	exit(g_status(-1));
}

static void	heredoc_loop(int *fds, t_tokens *redir_node, t_command *command,
		t_heredoc *here_struct)
{
	here_struct->delimiter = redir_node->next->word;
	here_struct->written_to_pipe = 0;
	here_struct->str = NULL;
	g_status(0);
	while (42)
	{
		here_struct->str = readline("> ");
		if (g_status(-1) == 130)
		{
			free_str(here_struct);
			break ;
		}
		if (handle_heredoc_input(fds, command, here_struct) == CLOSE)
			break ;
		free_str(here_struct);
		if (here_struct->written_to_pipe >= PIPE_BUF)
		{
			print_error("ms: heredoc limit reached, input'll be truncated\n");
			break ;
		}
	}
}

static int	handle_heredoc_input(int *fds, t_command *command,
		t_heredoc *here_struct)
{
	if (!(here_struct->str))
	{
		print_heredoc_ctrld(command->input_count, here_struct->delimiter);
		return (CLOSE);
	}
	else if (my_strcmp(here_struct->str, here_struct->delimiter) == 0)
		return (free_str(here_struct), CLOSE);
	else
	{
		if (only_spaces(here_struct->str) != ERROR)
			here_struct->str = expand_heredoc_variables(here_struct->str,
					command->my_env);
		here_struct->size = my_strlen(here_struct->str);
		here_struct->written_to_pipe += write(fds[1], here_struct->str,
				here_struct->size);
		here_struct->written_to_pipe += write(fds[1], "\n", 1);
	}
	return (NO_ERROR);
}

static void	free_str(t_heredoc *here_struct)
{
	free(here_struct->str);
	here_struct->str = NULL;
}
