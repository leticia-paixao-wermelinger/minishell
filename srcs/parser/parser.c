/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:41:24 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/07/23 19:13:23 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	input_parser(t_command *command)
{
	change_invalid_metachars(command);
//	my_printf("Ajuste de metachar inválido pré split c/ espaços: %s\n", command->input);
//	command->input = check_invalid_successive_metachars(command->input);
//	my_printf("Ajuste de metachar seguido pré split c/ espaços: %s\n", command->input);
	command->input = remove_spaces_around_metachars(command->input);
//	my_printf("Ajuste pré split s/ espaços: %s\n", command->input);
	//split de metacaracteres
	command->input_matrix = meta_split(command->input);
	command->input_matrix = return_invalid_metas(command, command->input_matrix);
//	my_printf("Input pós split de metacaracteres:\n");
//	print_matrix(command->input_matrix);
	make_list_from_input(command);
	//Imprimir a lista para teste
}
