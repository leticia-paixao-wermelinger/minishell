/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:05:26 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/06/28 19:32:38 by lpaixao-         ###   ########.fr       */
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

/*
enum e_error {
	NO_ERROR = 0,
	ERROR = 1,
	DIF = 2,
	ORDER = 3
};
*/
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
#endif
