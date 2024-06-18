/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 00:41:47 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/06/17 22:56:30 by lpaixao-         ###   ########.fr       */
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

int	main(void)
{
	char	*input;
	char	*prompt;

	while (42)
	{
		prompt = make_prompt();
		input = readline(prompt);
		add_history(input);
		if (my_strcmp(input, "exit") == 0)
		{
			free(input);
			break ;
		}
		printf("Passou pelas validações de erro\n");
		free(prompt);
		free(input);
	}
	rl_clear_history();
	free(prompt);
	printf("Exiting...\n");
}
