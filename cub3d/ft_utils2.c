/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <achatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 19:53:55 by achatela          #+#    #+#             */
/*   Updated: 2022/09/08 19:55:18 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_player(t_glob *glob, int size, int color)
{
	int	tmpy;
	int	tmpx;

	tmpy = glob->py;
	tmpx = glob->px;
	while (glob->py - tmpy < size)
	{
		while (glob->px - tmpx < size)
		{
			mlx_pixel_put(glob->mlx_ptr, glob->win_ptr, glob->px - size / 2,
				glob->py - size / 2, color);
			glob->px++;
		}
		glob->px = tmpx;
		glob->py++;
	}
	glob->py = tmpy;
}

int	ft_deal_key(int key, void *param)
{
	t_glob	*glob;

	glob = (t_glob *)param;
	if (key == ESC)
		return (ft_exit(glob), 1);
	if (key == TAB)
		return (1);
	if (key == M)
	{
		if (glob->minimap == 0)
			glob->minimap = 1;
		else if (glob->minimap == 1)
			glob->minimap = 0;
	}
	else if (key == Z || key == Q || key == S || key == D
		|| key == L_ARROW || key == R_ARROW)
		ft_move(glob, key);
	if (glob->minimap == 1)
	{
		ft_raycasting(glob);
		ft_minimap(glob);
	}
	else
		ft_raycasting(glob);
	return (0);
}
