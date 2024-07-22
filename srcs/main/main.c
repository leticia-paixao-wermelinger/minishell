/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 00:41:47 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/07/21 22:24:44 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	main(int argc, char *argv[])
{
	t_command	command;	

	if (argc > 1)
	{
		my_printf("bash: %s: No such file or directory\n", argv[1]);
		return 0;
	}
	get_env(&command);
	while (42)
	{
		set_command(&command);
		add_history(command.input);
		if (my_strcmp(command.input, "exit") == 0)
		{
			free(command.input);
			break ;
		}
		input_parser(&command);
		check_inputs(&command);
		free(command.prompt);
		free(command.input);
	}
	rl_clear_history();
	free(command.prompt);
	free(command.invalid_metas);
	free_list(command.my_env);
	printf("Exiting...\n");
}
/*
**com a my_env eu consigo fazer 3 built-ins: env (FEITA); export (cria uma nova variável de ambiente ou
altera uma que já existe) e unset (se ela conseguir achar a variável de ambiente, ela exclui essa
variável. Se não achar, não faz nada).
export = verifica se já existe. Se existe, modifica. Se não, cria uma nova.
ATENÇÃO PRO "VERIFICA DE EXISTE"!!! -> retorno de erro OU da posição!
Isso tb vai ser importante, depois, para a expansão de variáveis... "echo $USER", por exemplo, é
expansão de variável
Se conseguir modularizar a busca de uma variável de ambiente, a busca de erros, vai facilitar,
depois, na unset, na export e na expansão de variáveis (ver foto de echo c $User que não existe);
na régua de avaliação, se tiver $$ vai imprimir apenas um $, por mais q o bash coloque o pid
echo $? está pedindo p imprimir na tela o último erro (deu certo ou deu erra) -- ver foto de echo $?
*/
