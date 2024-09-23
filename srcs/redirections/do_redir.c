/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 00:13:51 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/09/23 00:14:06 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	do_heredoc(t_node *sentence, t_tokens *word)
{
	(void)sentence;
	(void)word;
	printf("Vai fazer heredoc\n");
	return (NO_ERROR);
}

int	do_append(t_node *sentence, t_tokens *word)
{
	(void)sentence;
	(void)word;
	printf("Vai fazer append\n");
	return (NO_ERROR);
}

int	do_redit_out(t_node *sentence, t_tokens *word)
{
	(void)sentence;
	(void)word;
	printf("Vai fazer redir_out\n");
	return (NO_ERROR);
}

int	do_redit_in(t_node *sentence, t_tokens *word)
{
	(void)sentence;
	(void)word;
	printf("Vai fazer redir_in\n");
	return (NO_ERROR);
}
