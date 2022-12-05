# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dsy <marvin@42.fr>                         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/13 16:01:25 by dsy               #+#    #+#              #
#    Updated: 2022/10/14 18:28:00 by dsy              ###   ########.fr        #
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

SRC_OTHER := main.c display.c exec.c utils/utils.c builtins/builtins_1.c \
			 init.c builtins/builtins_2.c builtins/builtins_runner.c \
			 utils/list_utils.c free.c envp.c expr.c utils/expr_utils.c \
			 builtins/ftn_builtins.c utils/ftn_utils.c pipex/pipe.c\
			 utils/check_quotes.c\

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

lib_fclean: libft_clean 

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
