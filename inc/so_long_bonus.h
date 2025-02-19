/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:40:17 by juaho             #+#    #+#             */
/*   Updated: 2025/02/19 11:24:21 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H
# define MAX_H 30
# define MAX_W 40
# define VALID_CHARS "01CEP\n"
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
	mlx_t		*mlx;
	mlx_image_t	**frames;
	size_t		frame_count;
	size_t		frame_index;
	double		accumulator;
}	t_anim;

typedef struct s_game
{
	t_map		*map;
	mlx_t		*mlx;
	mlx_image_t	*exit;
	mlx_image_t	*exit2;
	mlx_image_t	*player;
	mlx_image_t	*collect;
	mlx_image_t	*wall;
	mlx_image_t	*floor;
	t_anim		*anim1;
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
int		load_sprite_sheet(char *filename, mlx_t *mlx, t_anim **anim);
void	free_anim(t_anim *anim);

#endif
