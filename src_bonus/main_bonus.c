/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:23:42 by juaho             #+#    #+#             */
/*   Updated: 2025/02/21 12:31:51 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long_bonus.h"
#include "../libft/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <time.h>

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
	srand(time(NULL));
	mlx_close_hook(game.mlx, &close_hook, &game);
	mlx_key_hook(game.mlx, &input_keyhook, &game);
	mlx_loop_hook(game.mlx, &animation_hook, &game);
	mlx_loop_hook(game.mlx, &enemy_hook, &game);
	mlx_loop(game.mlx);
	close_game(&game, 0);
	return (1);
}
