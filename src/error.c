/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:48:27 by juaho             #+#    #+#             */
/*   Updated: 2025/02/21 11:18:11 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft/libft.h"
#include "../inc/so_long.h"

void	error_exit(char *emsg)
{
	char	*string;

	string = ft_strjoin("ERROR: ", emsg);
	ft_putendl_fd(string, 2);
	free(string);
	exit(1);
}

void	free_map_error_exit(t_map *map, char *emsg)
{
	free_grid(map->grid);
	error_exit(emsg);
}

void	error_close_game(t_game *game, char *emsg)
{
	char	*string;

	if (!emsg)
		ft_putstr_fd((char *) mlx_strerror(mlx_errno), 2);
	else
	{
		string = ft_strjoin("ERROR: ", emsg);
		ft_putendl_fd(string, 2);
		free(string);
	}
	close_game(game, 1);
}
