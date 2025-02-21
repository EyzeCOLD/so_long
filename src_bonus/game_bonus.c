/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:08:12 by juaho             #+#    #+#             */
/*   Updated: 2025/02/21 15:23:39 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long_bonus.h"
#include "../MLX42/include/MLX42/MLX42.h"

static int	load_images(t_game *game);
static int	load_image(char *filename, mlx_image_t **img, mlx_t *mlx);

void	init_game(t_game *game, char *map_file, int nightmode)
{
	init_map(map_file, game->map);
	game->mlx = mlx_init(game->map->w * 32, game->map->h * 32, "SO LONG", true);
	if (!game->mlx)
		error_close_game(game, NULL);
	if (load_images(game) < 0)
		error_close_game(game, NULL);
	game->moves = 0;
	game->nightmode = nightmode;
}

void	close_game(t_game *game, int exit_code)
{
	free_anim(game->player);
	free_anim(game->collect);
	free_anim(game->enemy);
	mlx_terminate(game->mlx);
	free_grid(game->map->grid);
	exit(exit_code);
}

static int	load_images(t_game *game)
{
	if (load_image("./sprites/exit.png", &game->exit, game->mlx) < 0)
		return (-1);
	if (load_image("./sprites/exit2.png", &game->exit2, game->mlx) < 0)
		return (-1);
	if (load_image("./sprites/wall_bonus.png", &game->wall, game->mlx) < 0)
		return (-1);
	if (load_image("./sprites/floor_bonus.png", &game->floor, game->mlx) < 0)
		return (-1);
	if (load_anim("./sprites/flame_bonus.png", game->mlx, &game->player) < 0)
		return (-1);
	if (load_anim("./sprites/drop_bonus.png", game->mlx, &game->enemy) < 0)
		return (-1);
	if (load_anim("./sprites/candle_bonus.png", game->mlx, &game->collect) < 0)
		return (-1);
	if (load_anim("./sprites/drop_bonus.png", game->mlx, &game->enemy) < 0)
		return (-1);
	return (0);
}

static int	load_image(char *filename, mlx_image_t **img, mlx_t *mlx)
{
	mlx_texture_t	*tex;

	tex = mlx_load_png(filename);
	if (tex)
	{
		*img = mlx_texture_to_image(mlx, tex);
		mlx_delete_texture(tex);
		if (*img)
			return (0);
	}
	return (-1);
}
