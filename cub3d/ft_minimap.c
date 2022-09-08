/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <achatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:51:36 by achatela          #+#    #+#             */
/*   Updated: 2022/09/08 19:19:02 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_square(t_glob *glob, int posx, int posy, int color)
{
	int	x;
	int	y;

	y = -1;
	while (++y < SCREEN_H / 8 / 5)
	{
		x = -1;
		while (++x < SCREEN_H / 8 / 5)
			mlx_pixel_put(glob->mlx_ptr,
				glob->win_ptr, posx + x, posy + y, color);
	}
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_minimap(t_glob *glob)
{
	int	i;

	i = 0;
	while (glob->map[i] != 0)
		i++;
	first_line(glob, SCREEN_H / 8 / 5);
	second_line(glob, SCREEN_H / 8 / 5);
	third_line(glob, SCREEN_H / 8 / 5);
	forth_line(glob, SCREEN_H / 8 / 5, i);
	fifth_line(glob, SCREEN_H / 8 / 5, i);
	ft_draw_square(glob, SCREEN_H / 8 / 5 * 2, SCREEN_H / 8 / 5 * 2, 16776960);
	return ;
}
