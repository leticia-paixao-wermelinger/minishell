/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listlib.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:44:04 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/06/27 23:11:38 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTLIB_H 
# define LISTLIB_H

# include "../../minishell.h"
# include "../my_libft/libft.h"

t_node	*create_first_node(char *c, t_node *list);
t_node	*create_last_node(char  *c, t_node *temp);
#endif
