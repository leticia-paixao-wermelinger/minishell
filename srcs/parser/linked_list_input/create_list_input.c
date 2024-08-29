/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 00:36:05 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/08/28 16:48:30 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	make_list_from_input(t_command *command)
{
//	t_node	*list;
	int		i;
	t_node	*temp;

	i = 0;
//	command->l_input = NULL;
	command->l_input = create_first_input_node(command->input_matrix[i], command->l_input);
//	printf("Node 0:\n");
//	printlist(command->l_input);
	temp = command->l_input;
	while (command->input_matrix[++i])
	//{
		temp = create_last_input_node(command->input_matrix[i], temp);
		//printf("Node %i:\n", i);
		//printlist(command->l_input);
	//}
}
