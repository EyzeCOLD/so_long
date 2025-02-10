/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:48:27 by juaho             #+#    #+#             */
/*   Updated: 2025/02/06 15:48:50 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft/libft.h"

void	error_exit(char *emsg)
{
	char	*string;

	string = ft_strjoin("ERROR: ", emsg);
	ft_putendl_fd(string, 2);
	free(string);
	exit(1);
}
