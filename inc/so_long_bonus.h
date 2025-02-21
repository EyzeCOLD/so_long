/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:40:17 by juaho             #+#    #+#             */
/*   Updated: 2025/02/21 10:38:50 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H
# define MAX_H 30
# define MAX_W 40
# define FRAME_TIME 0.2
# define ENEMY_TIME 1.6
# define VALID_CHARS "01CEPO\n"
# include <stdlib.h>
# include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_coord
{
	size_t	x;
	size_t	y;
}	t_coord;

typedef struct s_map
{
	char	*name;
	char	**grid;
	t_coord	p_pos;
	size_t	w;
	size_t	h;
	size_t	collectibles;
	int		exit_open;
}	t_map;

typedef struct s_anim
{
	int			enabled;
	mlx_t		*mlx;
	mlx_image_t	**frames;
	size_t		frame_count;
	size_t		frame_index;
	double		accumulator;
}	t_anim;

typedef struct s_game
{
	size_t		moves;
	t_map		*map;
	mlx_t		*mlx;
	mlx_image_t	*exit;
	mlx_image_t	*exit2;
	mlx_image_t	*wall;
	mlx_image_t	*floor;
	mlx_image_t	*movecounter;
	t_anim		*player;
	t_anim		*collect;
	t_anim		*enemy;
}	t_game;

/////////////////////////////////////////////////////////////// game_bonus.c //
void	init_game(t_game *game, char *map_file);
void	close_game(t_game *game, int exit_code);
//////////////////////////////////////////////////////////////// map_bonus.c //
void	init_map(char *file, t_map *map);
void	free_grid(char **grid);
/////////////////////////////////////////////////////// validate_map_bonus.c //
void	validate_map(t_map *map);
////////////////////////////////////////////////// validate_winnable_bonus.c //
void	validate_winnable(t_map *map);
/////////////////////////////////////////////////////////// draw_map_bonus.c //
void	draw_map(t_game *game);
//////////////////////////////////////////////////////// move_player_bonus.c //
void	move_player(t_game *game, int x, int y);
////////////////////////////////////////////////////////////// error_bonus.c //
void	error_exit(char *emsg);
void	free_map_error_exit(t_map *map, char *emsg);
void	error_close_game(t_game *game, char *emsg);
///////////////////////////////////////////////////// load_animation_bonus.c //
int		load_anim(char *filename, mlx_t *mlx, t_anim **anim);
void	free_anim(t_anim *anim);
//////////////////////////////////////////////////// animation_utils_bonus.c //
int		anim_to_window(mlx_t *mlx, t_anim *anim, size_t x, size_t y);
void	move_anim(t_anim *anim, t_coord *coord, int x, int y);
void	hide_anim_instance(t_anim *anim, t_coord *coord);
////////////////////////////////////////////////////////////// hooks_bonus.c //
void	close_hook(void *param);
void	input_keyhook(mlx_key_data_t keydata, void *param);
void	animation_hook(void *param);
void	enemy_hook(void *param);
////////////////////////////////////////////////////////////// enemy_bonus.c //
void	update_enemies(t_game *game);
void	player_collision(t_game *game);

#endif
