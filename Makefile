# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gadelbes <gadelbes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/01 15:23:49 by fparis            #+#    #+#              #
#    Updated: 2024/12/18 18:30:59 by mbico            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -O3 -g -Wall -Wextra -Werror
NAME = cub3D
NAME_BONUS = cub3D_bonus
HEADER = hdr
HEADER_BONUS = hdr_bonus
AUDIO_LIB =  lib/libmpg123.so lib/libportaudio.a
AUDIO_LIB_HEADER = -I ./lib/portaudio/include -I ./lib/mpg123-1.31.2/src/libmpg123

SRC_DIR = src
OBJ_DIR = obj

SRC_BONUS_DIR = src_bonus
OBJ_BONUS_DIR = obj_bonus

SRCS = main.c\
	   init.c\
	   close.c\
	   display/minimap/display_mm.c\
		display/minimap/circle_mm.c\
		display/minimap/init_mm.c\
		display/minimap/calc_mm.c\
		display/minimap/print_line_mm.c\
		display/minimap/rotation_mm.c\
	   display/display_rc.c\
	   display/display_utils.c\
		display/display_hud.c\
		display/display_text.c\
	   utils/check_approx.c\
	   utils/print_line.c\
	   utils/ft_map_len.c\
	   utils/time_utils.c\
	   utils/fps_counter.c\
	   utils/mutex_utils.c\
	   input/input.c\
	   input/input_action.c\
	   input/input_action_movement.c\
	   input/mouse.c\
	   input/mouse_action.c\
	   input/window_cross.c\
		parsing/fonction.c\
		parsing/parsing.c\
		parsing/error_map.c\
		parsing/error_id.c\
		parsing/tab_pars.c\
		parsing/utils/parsing_utils1.c\
		parsing/utils/parsing_utils2.c\
		parsing/utils/parsing_utils3.c\
		raycasting/dda.c\
		raycasting/dda_x.c\
		raycasting/dda_y.c\

SRCS_BONUS = main.c\
	   init.c\
	   close.c\
	   display/minimap/display_mm.c\
		display/minimap/circle_mm.c\
		display/minimap/init_mm.c\
		display/minimap/calc_mm.c\
		display/minimap/print_line_mm.c\
		display/minimap/rotation_mm.c\
	   display/display_rc.c\
	   display/display_utils.c\
		display/display_hud.c\
		display/display_text.c\
	   utils/check_approx.c\
	   utils/print_line.c\
	   utils/ft_map_len.c\
	   utils/time_utils.c\
	   utils/fps_counter.c\
	   utils/mutex_utils.c\
	   input/input.c\
	   input/input_action.c\
	   input/input_action_movement.c\
	   input/mouse.c\
	   input/mouse_action.c\
	   input/window_cross.c\
		parsing/fonction.c\
		parsing/parsing.c\
		parsing/error_map.c\
		parsing/error_id.c\
		parsing/tab_pars.c\
		parsing/utils/parsing_utils1.c\
		parsing/utils/parsing_utils2.c\
		parsing/utils/parsing_utils3.c\
		raycasting/dda.c\
		raycasting/dda_x.c\
		raycasting/dda_y.c\
		sound/ssys_init.c\
		sound/ssys_utils.c\
		sound/ssys_speaker.c

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)
OBJS_BONUS = $(SRCS_BONUS:%.c=$(OBJ_BONUS_DIR)/%.o)

RED = \033[0;31m
GREEN = \033[0;34m
YELLOW = \033[1;33m
PURPLE = \033[0;35m
NC = \033[0m

LIBFT = libft/libft.a
MLX = MacroLibX/libmlx.so

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $^ -o $(NAME) $(LIBFT) $(MLX) -I $(HEADER) -lm -lSDL2
	@echo "$(GREEN)$(NAME) compilation successful !$(NC)"

bonus: $(OBJS_BONUS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $^ -o $(NAME_BONUS) $(LIBFT) $(MLX) $(AUDIO_LIB) -I $(HEADER_BONUS) $(AUDIO_LIB_HEADER) -lpthread -lm -lasound -lSDL2
	@echo "$(GREEN)$(NAME_BONUS) Bonus compilation successful !$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling $(notdir $<)...$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER) -I ./libft -I ./MacroLibX/includes

$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling $(notdir $<)...$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER_BONUS) $(AUDIO_LIB_HEADER) -I ./libft -I ./MacroLibX/includes

$(MLX):
	@echo "$(PURPLE)Compiling MacroLibX...$(NC)"
	@make -C MacroLibX -j

$(LIBFT):
	@echo "$(PURPLE)Compiling libft...$(NC)"
	@make -C libft -j -s

clean:
	@echo "$(RED)Removing object...$(NC)"
	@rm -rf $(OBJ_DIR) $(OBJ_BONUS_DIR)
	@echo "$(RED)Removing libft object...$(NC)"
	@make -C libft clean -s
	@echo "$(RED)Removing mlx object...$(NC)"
	@make -C MacroLibX clean

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(NC)"
	@rm -f $(NAME)
	@echo "$(RED)Removing $(NAME_BONUS)...$(NC)"
	@rm -f $(NAME_BONUS)
	@echo "$(RED)Removing libft.a...$(NC)"
	@make -C libft fclean -s
	@echo "$(RED)Removing libmlx.so...$(NC)"
	@make -C MacroLibX fclean
	
re: fclean all

.PHONY: all bonus clean fclean re run
