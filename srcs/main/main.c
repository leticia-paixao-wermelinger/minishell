/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 00:41:47 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/08/22 20:30:44 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

volatile unsigned int    g_status;

//extern g_status;

int	main(int argc, char *argv[])
{
	t_command	command;	

	my_bzero(&command, sizeof(t_command));
	if (argc > 1)
	{
		my_printf("bash: %s: No such file or directory\n", argv[1]);
		return 0;
	}
	setup_signal_handling();
	get_env(&command);
	while (42)
	{
		printf("g_status = %i\n", g_status);
		set_command(&command);
		if (command.input == NULL)
		{
			clear_input(&command);
			break ;
		}
		add_history(command.input);
		input_parser(&command);
		lexer(&command);
//		printf("Printar lista do input:\n");
//		printlist(command.l_input);
		if (run_commands(&command) == CLOSE)
		{
			clear_loop_end(&command);
			break ;
		}
		clear_loop_end(&command);
	}
	final_clear(&command);
}
/*
**com a my_env eu consigo fazer 3 built-ins: env (FEITA); export (cria uma nova variável de ambiente ou
altera uma que já existe) e unset (FEITA) (se ela conseguir achar a variável de ambiente, ela exclui essa
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
