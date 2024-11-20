# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbico <mbico@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/01 15:23:49 by fparis            #+#    #+#              #
#    Updated: 2024/11/17 16:46:24 by mbico            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -O3 -g #-Wall -Wextra -Werror
NAME = cube3D
HEADER = hdr

SRC_DIR = src
OBJ_DIR = obj

SRCS = main.c\
	   init.c\
	   close.c\
	   display/display_mm.c\
	   display/circle_mm.c\
	   display/display_rc.c\
	   display/display_utils.c\
		display/display_hud.c\
	   utils/check_approx.c\
	   utils/print_line.c\
	   utils/ft_map_len.c\
	   input/input.c\
	   input/input_action.c\
	   input/mouse.c\
	   input/mouse_action.c\
		parsing/fonction.c\
		parsing/parsing.c\
		parsing/utils/parsing_utils3.c\
		parsing/error_map.c\
		parsing/error_id.c\
		parsing/tab_pars.c\
		parsing/utils/parsing_utils1.c\
		parsing/utils/parsing_utils2.c\
		raycasting/dda.c\
		raycasting/dda_x.c\
		raycasting/dda_y.c\

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

RED = \033[0;31m
GREEN = \033[0;34m
YELLOW = \033[1;33m
PURPLE = \033[0;35m
NC = \033[0m

LIBFT = libft/libft.a
MLX = MacroLibX/libmlx.so

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $^ -o $(NAME) $(LIBFT) $(MLX) -I $(HEADER) -lSDL2 -lm
	@echo "$(GREEN)$(NAME) compilation successful !$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling $(notdir $<)...$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER) -I ./libft -I ./MacroLibX/includes

$(MLX):
	@echo "$(PURPLE)Compiling MacroLibX...$(NC)"
	@make -C MacroLibX -j

$(LIBFT):
	@echo "$(PURPLE)Compiling libft...$(NC)"
	@make -C libft -j -s

clean:
	@echo "$(RED)Removing object...$(NC)"
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Removing libft object...$(NC)"
	@make -C libft clean -s
	@echo "$(RED)Removing mlx object...$(NC)"
	@make -C MacroLibX clean

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(NC)"
	@rm -f $(NAME)
	@echo "$(RED)Removing libft.a...$(NC)"
	@make -C libft fclean -s
	@echo "$(RED)Removing libmlx.so...$(NC)"
	@make -C MacroLibX fclean
	
re: fclean all

.PHONY: all clean fclean re run
