
NAME		= cub3d
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3
MLXFLAGS	= -lmlx -lXext -lX11 -lm

# Colors
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
RED			= \033[0;31m
BLUE		= \033[0;34m
RESET		= \033[0m

# Main sources
SRCS		= main.c \
			  init.c \
			  init_player_pos.c \
			  cleanup.c

# Directories
GAME_DIR	= game/
PARSE_DIR	= parsing/
RENDER_DIR	= render/
MATH_DIR	= math/

# Game sources
GAME_SRCS	= $(GAME_DIR)game_init.c \
			  $(GAME_DIR)gun.c \
			  $(GAME_DIR)hooks.c \
			  $(GAME_DIR)hooks_utils.c \
			  $(GAME_DIR)minimap.c \
			  $(GAME_DIR)movement.c

# Parsing sources
PARSE_SRCS	= $(PARSE_DIR)fill_grid.c \
			  $(PARSE_DIR)parse_color.c \
			  $(PARSE_DIR)parser.c \
			  $(PARSE_DIR)parser_element.c \
			  $(PARSE_DIR)parser_map.c \
			  $(PARSE_DIR)parser_utils.c \
			  $(PARSE_DIR)parse_texture.c \
			  $(PARSE_DIR)player_pos_utils.c \
			  $(PARSE_DIR)validate_map.c \
			  $(PARSE_DIR)validate_map_utils.c

# Render sources
RENDER_SRCS	= $(RENDER_DIR)raycast.c \
			  $(RENDER_DIR)texture.c \
			  $(RENDER_DIR)texture_load.c

# Math sources
MATH_SRCS	= $(MATH_DIR)dda.c \
			  $(MATH_DIR)vectors.c

# All sources combined
ALL_SRCS	= $(SRCS) $(GAME_SRCS) $(PARSE_SRCS) $(RENDER_SRCS) $(MATH_SRCS)

# Objects
OBJS_DIR	= objs/
OBJS		= $(addprefix $(OBJS_DIR), $(ALL_SRCS:.c=.o))

# Dependencies
DEPS		= $(OBJS:.o=.d)

# Libraries
LIBFT		= libft/libft.a
MLX			= minilibx-linux/libmlx.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -Llibft -lft -Lminilibx-linux $(MLXFLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) successfully created!$(RESET)"

$(OBJS_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -MMD -MP -I./includes -Ilibft -Iminilibx-linux -c $< -o $@

$(MLX):
	@echo "$(YELLOW)Compiling MLX...$(RESET)"
	@$(MAKE) -C minilibx-linux
	@echo "$(GREEN)MLX compilation successful!$(RESET)"

$(LIBFT):
	@echo "$(YELLOW)Compiling libft...$(RESET)"
	@$(MAKE) -C libft
	@echo "$(GREEN)Libft compilation successful!$(RESET)"

clean:
	@echo "$(YELLOW)Cleaning object files...$(RESET)"
	@$(MAKE) -C libft clean
	@$(MAKE) -C minilibx-linux clean
	@rm -rf $(OBJS_DIR)
	@echo "$(GREEN)Clean complete!$(RESET)"

fclean: clean
	@echo "$(YELLOW)Removing executables...$(RESET)"
	@$(MAKE) -C libft fclean
	@$(MAKE) -C minilibx-linux clean
	@rm -f $(NAME)
	@echo "$(GREEN)Full cleanup complete!$(RESET)"

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)