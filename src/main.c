/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:23:42 by juaho             #+#    #+#             */
/*   Updated: 2025/02/05 11:57:42 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"
#include "../libft/libft.h"

int main(int argc, char **argv)
{
	char	map[MAX_H][MAX_W + 2];

	if (argc != 2)
	{
		ft_printf("No map");
		return (1);
	}
	init_map(argv[1], map);
	for (int y = 0; y < MAX_H && map[y]; y++)
		ft_printf("%s", map[y]);
	return (0);
}
