/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:23:42 by juaho             #+#    #+#             */
/*   Updated: 2025/02/13 14:05:42 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"
#include "../libft/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"

static void	close_hook(void *param)
{
	t_game	*game;

	game = param;
	close_game(game, 0);
}

static void	input_keyhook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		close_game(game, 0);
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		move_player(game, -1, 0);
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		move_player(game, 1, 0);
	else if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		move_player(game, 0, -1);
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		move_player(game, 0, 1);
}

int	main(int argc, char **argv)
{
	t_map	map;
	t_game	game;

	if (argc != 2)
	{
		ft_printf("No map");
		return (1);
	}
	game.map = &map;
	init_game(&game, argv[1]);
	draw_map(&game);
	mlx_close_hook(game.mlx, &close_hook, &game);
	mlx_key_hook(game.mlx, &input_keyhook, &game);
	mlx_loop(game.mlx);
	close_game(&game, 0);
}
