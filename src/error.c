/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:48:27 by juaho             #+#    #+#             */
/*   Updated: 2025/02/12 11:13:33 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft/libft.h"
#include "../inc/so_long.h"

void	error_close_game(t_game *game)
{
	char	*emsg;

	emsg = ft_strjoin("ERROR: ", mlx_strerror(mlx_errno));
	if (emsg)
	{
		ft_putendl_fd(emsg, 2);
		free(emsg);
	}
	close_game(game, 1);
}
void	error_exit(char *emsg)
{
	char	*string;

	string = ft_strjoin("ERROR: ", emsg);
	if (string)
	{
		ft_putendl_fd(string, 2);
		free(string);
	}
	exit(1);
}

void	free_map_error_exit(t_map *map, char *emsg)
{
	free_grid(map->grid);
	error_exit(emsg);
}
