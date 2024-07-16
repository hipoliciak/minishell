# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/16 21:32:26 by dmodrzej          #+#    #+#              #
#    Updated: 2024/07/16 21:59:14 by dmodrzej         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

# compiler
CC		=	cc
FLAGS	=	-Wall -Wextra -Werror

# sources
SRC_DIR =	srcs/
SRC		=	main.c shell.c
SRCS	=	$(addprefix $(SRC_DIR), $(SRC))

# objects
OBJ_DIR	=	objs/
OBJ		=	$(SRC:.c=.o)
OBJS	=	$(addprefix $(OBJ_DIR), $(OBJ))

# includes
INC		=	-I includes -I libft

# libft
LIBFT_DIR	=	libft/
LIBFT_NAME	=	libft.a
LIBFT		=	$(LIBFT_DIR)$(LIBFT_NAME)

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
	@printf "] 100%%$(RESET)\n"
endef

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
			@$(CC) $(FLAGS) -c $< -o $@ $(INC)

all:		$(LIBFT) $(NAME)

$(NAME):	$(OBJS)
			@echo "$(CYAN)Compiling libs & program...$(NC)"
			@$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(INC)
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
