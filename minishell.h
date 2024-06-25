/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:05:26 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/06/25 12:52:31 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "my_libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>

/*
enum e_error {
	NO_ERROR = 0,
	ERROR = 1,
	DIF = 2,
	ORDER = 3
};

typedef struct s_node
{
	int				i;
	int				val;
	struct s_node	*next;
}	t_node;
*/

typedef struct s_command
{
	char	*input;
	char	*prompt;
	char	**my_env;
}	t_command;

char	*make_prompt(void);
char	**copy_env(char **envp, t_command *command);
void	set_command(t_command *command);
#endif
