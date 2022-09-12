/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <achatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:51:36 by achatela          #+#    #+#             */
/*   Updated: 2022/09/12 12:31:35 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strlen_lines(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

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
	first_line(glob, SCREEN_H / 8 / 5, -2, -1);
	second_line(glob, SCREEN_H / 8 / 5, -2, -1);
	third_line(glob, SCREEN_H / 8 / 5, -2, -1);
	forth_line(glob, SCREEN_H / 8 / 5, i, -3);
	fifth_line(glob, SCREEN_H / 8 / 5, i, -3);
	ft_draw_square(glob, SCREEN_H / 8 / 5 * 2, SCREEN_H / 8 / 5 * 2, 16776960);
	return ;
}
