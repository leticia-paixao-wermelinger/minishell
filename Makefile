# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/20 14:45:35 by lpaixao-          #+#    #+#              #
#    Updated: 2024/06/27 23:03:08 by lpaixao-         ###   ########.fr        #
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
declate_structs.c

OBJS = ${SRCS:.c=.o}

LIBFT = libs/my_libft/libft.a

LIBFT_PATH = libs/my_libft

LISTLIB = libs/listlib/listlib.a

LISTLIB_PATH = libs/my_libft

LIBS = $(LIBFT) $(LISTLIB)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(LIBS):
	make -s -C $(LIBFT_PATH)
	@echo "$(COLOUR_BLUE) libft is ready to be used$(COLOUR_END)"
	make -s -C $(LISTLIB_PATH)
	@echo "$(COLOUR_BLUE) listlib is ready to be used$(COLOUR_END)"

all: $(NAME)
	@echo "$(COLOUR_BLUE) minishell is ready to be used$(COLOUR_END)"

$(NAME): $(LIBS) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -lreadline -o $(NAME)

clean:
	make clean -C $(LIBFT_PATH)
	make clean -C $(LISTLIB_PATH)
	rm -f $(OBJS)
	@echo "$(COLOUR_RED)Objects deleted$(COLOUR_END)"

fclean: clean
	make fclean -C $(LIBFT_PATH)
	make fclean -C $(LISTLIB_PATH)
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
	$(CC) $(FLAGS) $(OBJS) $(LIBS) -lreadline -o $(NAME) -fsanitize=address
	./$(NAME)
