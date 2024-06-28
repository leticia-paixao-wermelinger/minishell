/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listlib.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:44:04 by lpaixao-          #+#    #+#             */
/*   Updated: 2024/06/28 12:59:21 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTLIB_H 
# define LISTLIB_H

# include "../../minishell.h"
# include "../my_libft/libft.h"

struct s_node	*create_first_node(char *c, struct s_node *list);
struct s_node	*create_last_node(char  *c, struct s_node *temp);
#endif
