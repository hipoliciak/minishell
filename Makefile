# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/16 21:32:26 by dmodrzej          #+#    #+#              #
#    Updated: 2024/07/21 16:35:50 by dkolida          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

# compiler
CC		=	cc
FLAGS	=	-Wall -Wextra -Werror

# sources
SRC_DIR		=	srcs/
SRC			=	$(shell find $(SRC_DIR) -type f -name '*.c')

# objects
OBJ_DIR =	objs/
OBJ		=	$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# libft
LIBFT_DIR	=	libft/
LIBFT		=	$(LIBFT_DIR)libft.a

# readline (macOS)
READLINE_DIR	=	/opt/homebrew/opt/readline
READLINE_INC	=	-I $(READLINE_DIR)/include
READLINE_LIB	=	-L $(READLINE_DIR)/lib -lreadline
# readline (Linux) #TODO check if it works on Linux
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	READLINE_DIR	=	/usr/include/readline
endif

# includes
INC		=	-I includes -I libft $(READLINE_INC)

# colors & symbols
GREEN 	= 	\033[0;32m
CYAN	=	\033[0;36m
NC		= 	\033[0m
TICK	=	✅

define PRINT_LOADING
	@printf "$(CYAN)["
	@for i in $$(seq 0 10 100); do \
		printf "▓"; \
		sleep 0.1; \
	done
	@printf "] 100%%$(NC)\n"
endef

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
			@mkdir -p $(dir $@)
			@$(CC) $(FLAGS) -c $< -o $@ $(INC)

all:		$(OBJ_DIR) $(LIBFT) $(NAME)

$(NAME):	$(OBJ)
			@echo "$(CYAN)Compiling libs & program...$(NC)"
			@$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(LIBFT) $(INC) $(READLINE_LIB)
			@$(PRINT_LOADING)
			@echo "$(GREEN)Program compilation successful		$(TICK)$(NC)"

$(OBJ_DIR):
			@mkdir -p $(OBJ_DIR)

$(LIBFT):
			@make -sC $(LIBFT_DIR)

clean:
			@echo "$(CYAN)Cleaning .o files...$(NC)"
			@make clean -sC $(LIBFT_DIR)
			@rm -rf $(OBJ_DIR)
			@$(PRINT_LOADING)
			@echo "$(GREEN)Cleaning of of .o files successful	$(TICK)$(NC)"

fclean:		clean
			@echo "$(CYAN)Cleaning libs & main program...$(NC)"
			@rm -f $(NAME) $(LIBFT)
			@$(PRINT_LOADING)
			@echo "$(GREEN)Full cleaning successful		$(TICK)$(NC)"

re:			fclean all

.PHONY:		all clean fclean re
