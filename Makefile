# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/20 14:45:35 by lpaixao-          #+#    #+#              #
#    Updated: 2024/06/17 18:23:40 by lpaixao-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_YELLOW=\033[0;33m
COLOUR_GREY=\033[0;90m
COLOUR_END=\033[0m

NAME = minishell

CC = cc

FLAGS = -Wall -Wextra -Werror -g

SRCS = \
main.c \

OBJS = ${SRCS:.c=.o}

LIBFT = my_libft/libft.a

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(LIBFT):
	make -s -C my_libft
	@echo "$(COLOUR_BLUE) libft is ready to be used$(COLOUR_END)"

all: $(NAME)
	@echo "$(COLOUR_BLUE) minishell is ready to be used$(COLOUR_END)"

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

clean:
	make clean -C my_libft
	rm -f $(OBJS)
	@echo "$(COLOUR_RED)Objects deleted$(COLOUR_END)"

fclean: clean
	make fclean -C my_libft
	rm -f $(NAME)
	@echo "$(COLOUR_RED)All cleaned$(COLOUR_END)"

re: fclean all

run: re
	./$(NAME)

val: re
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

norm:
		@echo "$(COLOUR_BLUE)Passando a Norminette com a flag -R CheckForbiddenSourceHeader: $(COLOUR_END)"
	@-norminette -R CheckForbiddenSourceHeader

sanitize: fclean $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -lreadline -o $(NAME) -fsanitize=address
	./$(NAME)
