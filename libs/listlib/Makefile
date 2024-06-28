# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/27 18:44:39 by lpaixao-          #+#    #+#              #
#    Updated: 2024/06/28 15:51:06 by lpaixao-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = listlib.a

CC = cc

FLAGS = -Wall -Wextra -Werror -g

SRCS = \
create_first_node.c \
create_last_node.c \

OBJS = ${SRCS:.c=.o}

LIBFT = ../my_libft/libft.a

LIBFT_PATH = ../my_libft

.c.o:
	$(CC) $(FLAGS) -c $< -o $@

$(LIBFT):
	make -s -C $(LIBFT_PATH)

all: $(LIBFT) ${NAME}

${NAME} : $(OBJS)
	ar -rcs $(NAME) $(OBJS)

clean:
	make clean -C $(LIBFT_PATH)
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_PATH)
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
