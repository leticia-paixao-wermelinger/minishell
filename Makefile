# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/20 14:45:35 by lpaixao-          #+#    #+#              #
#    Updated: 2024/09/24 09:35:18 by lpaixao-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# GE = GREEN
# BL = BLUE
# RD = RED
# YL = YELLOW
# GR = GREY
# BL = BLINK
# BD = BOLD
# RESET

GE=\033[32m
RD=\033[31m
BL=\033[34m
YL=\033[33m
GR=\033[90m
BOLD=\033[1m
GE_BD_BL=\033[1;5;32m

BLINK = \033[6;7;1;3m
RESET=\033[0m

NAME = minishell

CC = cc

FLAGS = -Wall -Wextra -Werror -g \

RL_FLAG = -lreadline \

OS := $(shell uname)
ifeq ($(OS), Darwin)

FLAGS += -I$(shell brew --prefix readline)/include
RL_FLAG += -L$(shell brew --prefix readline)/lib
endif

SRCS = \
srcs/main/main.c \
srcs/main/prompt_and_inputs.c \
srcs/main/pre_exec.c \
\
srcs/parser/parser.c \
srcs/parser/tokenize_words.c \
srcs/parser/linked_list_input/create_list_input.c \
\
srcs/error_handle/input_validation.c \
srcs/error_handle/pipe_and_redir_validation.c \
srcs/error_handle/pipe_validation.c \
srcs/error_handle/print_error.c \
srcs/error_handle/quote_validation.c \
srcs/error_handle/redir_validation.c \
srcs/error_handle/remove_quotes.c \
srcs/error_handle/errors_utils.c \
\
srcs/general_functions/is_chars_functions.c \
srcs/general_functions/is_chars_functions_2.c \
srcs/general_functions/is_chars_functions_3.c \
\
srcs/signals/signal_handle.c \
\
srcs/linked_list/change_list.c \
srcs/linked_list/list_functions.c \
\
srcs/redirections/find_redir.c \
srcs/redirections/do_redir.c \
srcs/redirections/redir_utils.c \
\
srcs//variable_expansion/var_exp.c \
srcs//variable_expansion/var_exp_utils.c \
\
srcs/env/env_utils.c \
\
srcs/exec/clean_execve.c \
srcs/exec/executor.c \
srcs/exec/execve_utils.c \
srcs/exec/init_execve.c \
srcs/exec/pipe_execution.c \
srcs/exec/run_execve.c \
srcs/exec/fd.c \
\
srcs/builtints/builtins.c \
srcs/builtints/cd.c \
srcs/builtints/echo.c \
srcs/builtints/exit.c \
srcs/builtints/pwd.c \
srcs/builtints/env/env_bt_utils.c \
srcs/builtints/env/env_builtins.c \
\
srcs/cleaning/clear_funct.c

OBJS = ${SRCS:.c=.o}

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

LIBFT = libs/my_libft/libft.a

LIBFT_PATH = libs/my_libft

LIBS = $(LIBFT)

all: $(NAME)
	@echo "$(BLINK)$(BOLD)$(BL)✅ minishell is ready to be used$(RESET)"

$(LIBS):
	make -s -C $(LIBFT_PATH)
	@echo "$(BL)📚 libft is ready to be used$(RESET)"

$(NAME): $(LIBS) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LIBS) $(RL_FLAG) -o $(NAME)

clean:
	make clean -C $(LIBFT_PATH)
	rm -f $(OBJS)
	@echo "$(BOLD)$(RD)📤 Objects deleted$(RESET)"

fclean: clean
	make fclean -C $(LIBFT_PATH)
	rm -f $(NAME)
	@echo "$(BLINK)$(BOLD)$(RD)🧼 All cleaned$(RESET)"

re: fclean all

run: re
	./$(NAME)

val: re
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=supressions.supp ./$(NAME)

norm:
	@echo "$(BL)Passando a Norminette com a flag -R CheckForbiddenSourceHeader: $(RESET)"
	@-norminette -R CheckForbiddenSourceHeader

sanitize: fclean $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LIBS) $(RL_FLAG) -o $(NAME) -fsanitize=address
	./$(NAME)
