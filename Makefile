#####  FILES  ##################################################################

NAME := ./bin/so_long

SRC_DIR := ./src/
SRC := \
	main.c				init_map.c				error.c		\
	validate_map.c		validate_winnable.c		init_game.c	\
	draw_map.c			move_player.c
SRC := $(addprefix $(SRC_DIR), $(SRC))

OBJ_DIR := ./obj/
OBJ := $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

INC := ./inc/so_long.h

#BONUS--------------------------------------------------------------------------
BONUS := ./bin/so_long_bonus

BONUS_SRC_DIR := ./src_bonus/
BONUS_SRC := \
	draw_map_bonus.c		error_bonus.c				\
	game_bonus.c			map_bonus.c					\
	main_bonus.c			move_player_bonus.c			\
	validate_map_bonus.c	validate_winnable_bonus.c	\
	animation_bonus.c		animation_utils_bonus.c		\
	hooks_bonus.c			enemy_bonus.c
BONUS_SRC := $(addprefix $(BONUS_SRC_DIR), $(BONUS_SRC))

BONUS_OBJ_DIR := ./obj_bonus/
BONUS_OBJ := $(patsubst $(BONUS_SRC_DIR)%.c, $(BONUS_OBJ_DIR)%.o, $(BONUS_SRC))

BONUS_INC := ./inc/so_long_bonus.h

#LIBFT- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
LIBFT := ./libft/libft.a

#MLX42- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
MLX42 := ./MLX42/build/libmlx42.a
MLX42_FLAGS := -Iinclude -ldl -lglfw -pthread -lm

#####  COMPILERS  ##############################################################

CC := cc

CFLAGS := -Wall -Wextra -Werror

#####  RULES  ##################################################################

all: $(MLX42) $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX42) $(MLX42_FLAGS) -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p obj

#BONUS--------------------------------------------------------------------------
bonus: $(MLX42) $(BONUS)

$(BONUS): $(LIBFT) $(BONUS_OBJ_DIR) $(BONUS_OBJ)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBFT) $(MLX42) $(MLX42_FLAGS) -o $@

$(BONUS_OBJ_DIR)%.o: $(BONUS_SRC_DIR)%.c $(BONUS_INC)
	$(CC) $(CFLAGS) -c $< -o $@

$(BONUS_OBJ_DIR):
	@mkdir -p obj_bonus

#LIBFT- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
$(LIBFT):
	@(cd libft && make)

#MLX42- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
$(MLX42): .mlxcloned

.mlxcloned:
	git clone https://github.com/codam-coding-college/MLX42.git
	cd MLX42 && cmake -B build && cmake --build build -j4
	@touch .mlxcloned

#CLEANUP------------------------------------------------------------------------
clean:
	@rm -rf $(OBJ_DIR) $(BONUS_OBJ_DIR) .bonus

fclean: clean
	@rm -rf $(NAME) $(BONUS)
	@rm -rf bin

re: fclean all

reb: fclean bonus

#DEBUG--------------------------------------------------------------------------
debug: CFLAGS := $(CFLAGS) -g
debug: all

debugb: CFLAGS := $(CFLAGS) -g
debugb: bonus

.PHONY: all clean fclean re debug phony bonus reb debugb
