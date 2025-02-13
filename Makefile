#####  FILES  ##################################################################

NAME := ./bin/so_long

SRC_DIR := ./src/
SRC := main.c				init_map.c				error.c		\
	   validate_map.c		validate_winnable.c		init_game.c	\
	   draw_map.c			move_player.c
SRC := $(addprefix $(SRC_DIR), $(SRC))

OBJ_DIR := ./obj/
OBJ := $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

INC := ./inc/so_long.h

#  LIBFT

LIBFT := ./libft/libft.a

#  MLX42

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

$(LIBFT): phony
	@(cd libft && make)

$(MLX42): .mlxcloned

.mlxcloned:
	git clone https://github.com/codam-coding-college/MLX42.git
	cd MLX42 && cmake -B build && cmake --build build -j4
	@touch .mlxcloned

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p obj

clean:
	@rm -rf $(OBJ_DIR) .bonus

fclean: clean
	@rm -rf $(NAME) $(BONUS)
	@rm -rf bin

re: fclean all

#  DEBUG

debug: CFLAGS := $(CFLAGS) -g
debug: all

.PHONY: all clean fclean re debug phony
