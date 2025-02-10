/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:40:17 by juaho             #+#    #+#             */
/*   Updated: 2025/02/06 15:41:50 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# define MAX_H 30
# define MAX_W 40
# define VALID_CHARS "01CEP\n"

///////////////////////////////////////////////////////////////// init_map.c //
void	init_map(char *file, char map[MAX_H][MAX_W + 2]);
///////////////////////////////////////////////////////////// validate_map.c //
void	validate_map(char map[MAX_H][MAX_W + 2]);
//////////////////////////////////////////////////////////////////// error.c //
void	error_exit(char *emsg);

#endif
