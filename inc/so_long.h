/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:40:17 by juaho             #+#    #+#             */
/*   Updated: 2025/02/20 12:11:36 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
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
}	t_game;

//////////////////////////////////////////////////////////////// init_game.c //
void	init_game(t_game *game, char *map_file);
void	close_game(t_game *game, int exit_code);
///////////////////////////////////////////////////////////////// init_map.c //
void	init_map(char *file, t_map *map);
void	free_grid(char **grid);
///////////////////////////////////////////////////////////// validate_map.c //
void	validate_map(t_map *map);
//////////////////////////////////////////////////////// validate_winnable.c //
void	validate_winnable(t_map *map);
///////////////////////////////////////////////////////////////// draw_map.c //
void	draw_map(t_game *game);
////////////////////////////////////////////////////////////// move_player.c //
void	move_player(t_game *game, int x, int y);
//////////////////////////////////////////////////////////////////// error.c //
void	error_exit(char *emsg);
void	free_map_error_exit(t_map *map, char *emsg);
void	error_close_game(t_game *game, char *emsg);

#endif
