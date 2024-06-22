/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 00:41:47 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/06/20 15:38:29 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_prompt(void)
{
	char	cwd[1824];
	char	*prompt;
	char	*temp;

	getcwd(cwd, sizeof(cwd));
	temp = my_strjoin("\033[0;32m", cwd);
	prompt = my_strjoin(temp, "\033[0m$ ");
	free(temp);
	return (prompt);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_command	command;	
/*	char	*input;
	char	*prompt;*/

	(void)argc;
	(void)argv;
	(void)envp;
	while (42)
	{
		set_command(&command);
/*		prompt = make_prompt();
		input = readline(prompt);*/
		add_history(command.input);
		if (my_strcmp(command.input, "exit") == 0)
		{
			free(command.input);
			break ;
		}
		free(command.prompt);
		free(command.input);
	}
	rl_clear_history();
	free(command.prompt);
	printf("Exiting...\n");
}
/*
**envp para pegar as variáveis de ambiente (no bash, só digitar "env");
*/
