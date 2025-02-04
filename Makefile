# Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
BLUE = \033[0;34m
RESET = \033[0m

NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -lmlx -lXext -lX11 -lm

# Source files
SRCS = $(wildcard *.c)
PARSING_SRCS = $(wildcard parsing/*.c)
GAME_SRCS = $(wildcard game/*.c)
RENDER_SRCS = $(wildcard render/*.c)
MATH_SRCS = $(wildcard math/*.c)
ALL_SRCS = $(SRCS) $(PARSING_SRCS) $(GAME_SRCS) $(RENDER_SRCS) $(MATH_SRCS)

OBJS_DIR = objs
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o) \
       $(PARSING_SRCS:parsing/%.c=$(OBJS_DIR)/parsing/%.o) \
       $(GAME_SRCS:game/%.c=$(OBJS_DIR)/game/%.o) \
       $(RENDER_SRCS:render/%.c=$(OBJS_DIR)/render/%.o) \
       $(MATH_SRCS:math/%.c=$(OBJS_DIR)/math/%.o)

DEPS = $(OBJS:.o=.d)

LIBFT = libft/libft.a
MLX = minilibx-linux/libmlx.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) -Llibft -lft -Lminilibx-linux $(MLXFLAGS) -o $(NAME) || \
		(echo "$(RED)Linking failed!$(RESET)" && exit 1)
	@echo "$(GREEN)$(NAME) successfully created!$(RESET)"

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -MMD -MP -I./includes -Ilibft -Iminilibx-linux -c $< -o $@ || \
		(echo "$(RED)Compilation of $< failed!$(RESET)" && exit 1)

$(OBJS_DIR)/parsing/%.o: parsing/%.c
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -MMD -MP -I./includes -Ilibft -Iminilibx-linux -c $< -o $@ || \
		(echo "$(RED)Compilation of $< failed!$(RESET)" && exit 1)

$(OBJS_DIR)/game/%.o: game/%.c
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -MMD -MP -I./includes -Ilibft -Iminilibx-linux -c $< -o $@ || \
		(echo "$(RED)Compilation of $< failed!$(RESET)" && exit 1)

$(OBJS_DIR)/render/%.o: render/%.c
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -MMD -MP -I./includes -Ilibft -Iminilibx-linux -c $< -o $@ || \
		(echo "$(RED)Compilation of $< failed!$(RESET)" && exit 1)

$(OBJS_DIR)/math/%.o: math/%.c
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -MMD -MP -I./includes -Ilibft -Iminilibx-linux -c $< -o $@ || \
		(echo "$(RED)Compilation of $< failed!$(RESET)" && exit 1)

$(MLX):
	@echo "$(YELLOW)Compiling MLX...$(RESET)"
	@$(MAKE) -C minilibx-linux || \
		(echo "$(RED)MLX compilation failed!$(RESET)" && exit 1)
	@echo "$(GREEN)MLX compilation successful!$(RESET)"

$(LIBFT):
	@echo "$(YELLOW)Compiling libft...$(RESET)"
	@$(MAKE) -C libft || \
		(echo "$(RED)Libft compilation failed!$(RESET)" && exit 1)
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