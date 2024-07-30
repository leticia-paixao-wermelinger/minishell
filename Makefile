# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/20 14:45:35 by lpaixao-          #+#    #+#              #
#    Updated: 2024/07/29 22:20:09 by lpaixao-         ###   ########.fr        #
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
srcs/main/main.c \
srcs/linked_list/list_functions.c \
srcs/linked_list/change_list.c \
srcs/cleaning/clear_funct.c \
srcs/builtints/env/env_builtins.c \
srcs/builtints/env/env_utils.c \
srcs/parser/parser.c \
srcs/parser/quot_marks_validation/parser_quotation_marks_validation.c \
srcs/parser/quot_marks_validation/str_of_invalid_metas.c \
srcs/parser/spaces_around_metas/spaces_around_metas_validation.c \
srcs/parser/spaces_around_metas/strlen_spaces_around_metas.c \
srcs/parser/meta_split.c \
srcs/lexer/lexer.c \
srcs/lexer/find_token/set_token_1.c \
srcs/lexer/find_token/set_token_2.c \
srcs/general_metachar_functions/metacharacters_utils.c \
srcs/main/prompt_and_inputs.c \
srcs/builtints/builtins.c \
srcs/builtints/pwd.c \
srcs/parser/linked_list_input/create_list_input.c

OBJS = ${SRCS:.c=.o}

LIBFT = libs/my_libft/libft.a

LIBFT_PATH = libs/my_libft

#LISTLIB = libs/listlib/listlib.a

#LISTLIB_PATH = libs/listlib

LIBS = $(LIBFT) #$(LISTLIB)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(LIBS):
	make -s -C $(LIBFT_PATH)
	@echo "$(COLOUR_BLUE) libft is ready to be used$(COLOUR_END)"
	#make re -s -C $(LISTLIB_PATH) #Não sei pq apenas o make do Makefile dessa lib não está funcionando...
	#@echo "$(COLOUR_BLUE) listlib is ready to be used$(COLOUR_END)"

all: $(NAME)
	@echo "$(COLOUR_BLUE) minishell is ready to be used$(COLOUR_END)"

$(NAME): $(LIBS) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LIBS) -lreadline -o $(NAME)

clean:
	make clean -C $(LIBFT_PATH)
	#make clean -C $(LISTLIB_PATH)
	rm -f $(OBJS)
	@echo "$(COLOUR_RED)Objects deleted$(COLOUR_END)"

fclean: clean
	make fclean -C $(LIBFT_PATH)
	#make fclean -C $(LISTLIB_PATH)
	rm -f $(NAME)
	@echo "$(COLOUR_RED)All cleaned$(COLOUR_END)"

re: fclean all

run: re
	./$(NAME)

val: re
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=supressions.supp ./$(NAME)

norm:
		@echo "$(COLOUR_BLUE)Passando a Norminette com a flag -R CheckForbiddenSourceHeader: $(COLOUR_END)"
	@-norminette -R CheckForbiddenSourceHeader

sanitize: fclean $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LIBS) -lreadline -o $(NAME) -fsanitize=address
	./$(NAME)
