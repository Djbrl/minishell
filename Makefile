# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dsy <marvin@42.fr>                         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/13 16:01:25 by dsy               #+#    #+#              #
#    Updated: 2023/02/23 12:28:07 by dsy              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#---------------------------------VARIABLES------------------------------------#

GREEN_COLOR = \033[0;32m
YLW_COLOR = \033[0;33m
END_COLOR = \033[0m
NAME := minishell

LIB_FT := libft/libft.a

CC := cc
CFLAGS := -Wall -Wextra -Werror
CPFLAGS := -g3#-lreadline
PFLAGS := -Iinclude -Ilibft

SRC_OTHER := main.c exec.c init.c envp.c expr.c\
			 \
			 utils/list.c utils/status_signal_expr.c utils/free_exit.c \
			 utils/split_charset.c utils/read_expand_builtin.c utils/sort_env.c\
			 utils/get_next_line.c utils/display.c utils/exit_shell.c \
			 utils/promptline.c utils/read_parsing.c utils/set_prompt.c \
			 utils/single_exec_utils.c \
			 \
			 pipes/pipe.c pipes/pipe_utils.c pipes/pipe_child.c pipes/pipe_exec.c \
			 \
			 redirections/redirections.c redirections/redirections_utils.c \
			 redirections/check_redirections.c redirections/child_heredoc.c \
			 redirections/redir_handlers.c redirections/heredoc_expand.c \
			 \
			 builtins/echo_runner.c builtins/export_runner.c \
			 builtins/other.c builtins/export.c builtins/unset.c \
			 builtins/echo.c builtins/cd.c builtins/cd_extension.c \
			 \
			 parsing/parse_prompt.c parsing/cases/dollar.c \
			 parsing/cases/double_quote.c parsing/cases/single_quote.c \
			 parsing/cases/pipe_redir.c parsing/cases/string.c \
			 parsing/utils/add_to_rt.c parsing/utils/ft_realloc.c \
			 parsing/utils/is_pipe_redir.c parsing/utils/is_whitespace.c \
			 parsing/utils/pipe_redir_inside_quotes.c parsing/expand_prompt.c \

SRC_PATH := src
SRC_NAME := $(SRC_OTHER)

OBJ_PATH := obj
OBJ_NAME := $(SRC_NAME:.c=.o)

INCDIR := include
BUILD_PATH := build

SRC := $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ := $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
OBJ := $(addprefix $(BUILD_PATH)/,$(OBJ))

#---------------------------------VARIABLES------------------------------------#

all: $(NAME)
	@echo "Ready : ${GREEN_COLOR}`pwd`/${NAME}${END_COLOR}"

$(NAME): $(OBJ) $(LIB_FT)
	@$(CC) $(OBJ) $(LIB_FT) $(CFLAGS) $(CPFLAGS) -o $(NAME) -lreadline

$(BUILD_PATH)/$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(dir $@) 2>/dev/null || true
	@$(CC) $(CFLAGS) $(CPFLAGS) $(PFLAGS) -c $< -o $@

$(LIB_FT):
	@echo "${YLW_COLOR}Compiling ${NAME}...${END_COLOR}"
	@make -C libft

libft_clean:
	@make -C libft clean

libft_fclean:
	@make -C libft fclean

lib_clean: libft_clean 

lib_fclean: libft_fclean 

re: fclean all

clean: lib_clean
	@rm -rf $(OBJ)
	@rm -rf $(BUILD_PATH)/$(OBJ_PATH)
	@echo "Clean : $(YLW_COLOR)/$(BUILD_PATH)${END_COLOR}"

fclean : lib_fclean
	@rm -rf $(NAME)
	@rm -rf $(BUILD_PATH)
	@echo "Clean : $(YLW_COLOR)/$(BUILD_PATH)${END_COLOR}"
	@echo "Clean : $(YLW_COLOR)/$(NAME)${END_COLOR}"

make noenv: all
	env -i valgrind --leak-check=full --show-leak-kinds=definite ./minishell

FORCE:

.PHONY: all, clean, fclean, re
