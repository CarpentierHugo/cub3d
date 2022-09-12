/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modelisation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <achatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:52:13 by achatela          #+#    #+#             */
/*   Updated: 2022/09/12 15:50:55 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_find_wall(t_glob *glob, float ty)
{
	float	tx;

	tx = (int)(((int)glob->rx + (int)glob->ry) / (SQR / RES)) % RES;
	if (glob->map[(int)((glob->ry - 1) / SQR)][(int)(glob->rx / SQR)] != '1'
		&& (int)((glob->ry - 1) / SQR) == (int)((glob->s) / SQR))
		return (glob->n_img->data[(int)tx + (int)ty * RES]);
	else if (glob->map[(int)((glob->ry + 1) / SQR)][(int)(glob->rx / SQR)]
		!= '1' && (int)((glob->ry + 1) / SQR) == (int)((glob->s) / SQR))
		return (glob->s_img->data[(int)tx + (int)ty * RES]);
	else if (glob->map[(int)(glob->ry / SQR)][(int)((glob->rx + 1) / SQR)]
		!= '1' && (int)((glob->rx + 1) / SQR) == (int)((glob->c) / SQR))
		return (glob->e_img->data[(int)tx + (int)ty * RES]);
	else if (glob->map[(int)(glob->ry / SQR)][(int)((glob->rx - 1) / SQR)]
		!= '1' && (int)((glob->rx - 1) / SQR) == (int)((glob->c) / SQR))
		return (glob->w_img->data[(int)tx + (int)ty * RES]);
	else if ((glob->ra <= PI / 4 && glob->ra >= 0) || (glob->ra
			>= 7 * PI / 4 && glob->ra <= 2 * PI))
		return (glob->w_img->data[(int)tx + (int)ty * RES]);
	else if (glob->ra >= 5 * PI / 4 && glob->ra <= 7 * PI / 4)
		return (glob->s_img->data[(int)tx + (int)ty * RES]);
	else if (glob->ra >= 3 * PI / 4 && glob->ra <= 5 * PI / 4)
		return (glob->e_img->data[(int)tx + (int)ty * RES]);
	else
		return (glob->n_img->data[(int)tx + (int)ty * RES]);
}

float	ft_premod(t_glob *glob, int *lineo, float *lineh, float *ty_step)
{
	float	ty_off;
	float	ca;

	ca = glob->pa - glob->ra;
	if (ca < 0)
		ca += 2 * PI;
	if (ca > 2 * PI)
		ca -= 2 * PI;
	glob->length *= cos(ca);
	*lineh = SQR * SCREEN_H / glob->length;
	*ty_step = RES / *lineh;
	ty_off = 0;
	if (*lineh > SCREEN_H)
	{
		ty_off = (*lineh - SCREEN_H) / 2;
		*lineh = SCREEN_H;
	}
	*lineo = SCREEN_H / 2 - (*lineh / 2);
	return (ty_off * *ty_step);
}

void	ft_modelisation(t_glob *glob, int i)
{
	float	lineh;
	int		lineo;
	int		y;
	float	ty;
	float	ty_step;

	ty = ft_premod(glob, &lineo, &lineh, &ty_step);
	y = -1;
	glob->s = glob->ry - sin(glob->ra);
	glob->c = glob->rx - cos(glob->ra);
	while (++y < lineh)
	{
		glob->data[(int)(i + (y + lineo) * SCREEN_W)]
			= ft_find_wall(glob, ty);
		ty += ty_step;
	}
	y = -1;
	while (++y < lineo)
		glob->data[(int)(i + y * SCREEN_W)] = glob->ceiling;
	y = lineo + lineh - 1;
	while (++y < SCREEN_H)
		glob->data[(int)(i + y * SCREEN_W)] = glob->floor;
}

void	ft_ray_maker(t_glob *glob, int i)
{
	float	sinra;
	float	cosra;

	while (++i < SCREEN_W)
	{
		glob->rx = glob->px;
		glob->ry = glob->py;
		glob->length = 0;
		cosra = cos(glob->ra);
		sinra = sin(glob->ra);
		while (glob->map[(int)(glob->ry / SQR)][(int)(glob->rx / SQR)] != '1'
			&& glob->map[(int)(glob->ry / SQR)][(int)(glob->rx / SQR)]
			!= '\0' && glob->map[(int)(glob->ry / SQR)]
			[(int)(glob->rx / SQR)] != ' ')
		{
			glob->rx += cosra;
			glob->ry += sinra;
			glob->length++;
		}
		ft_modelisation(glob, i);
		glob->ra += DR * FOV / SCREEN_W;
		if (glob->ra > 2 * PI)
			glob->ra -= 2 * PI;
	}
}

void	ft_raycasting(t_glob *glob)
{
	glob->ra = glob->pa - DR * (FOV / 2);
	if (glob->ra < 0)
		glob->ra += 2 * PI;
	ft_ray_maker(glob, -1);
	mlx_put_image_to_window(glob->mlx_ptr, glob->win_ptr, glob->image, 0, 0);
	mlx_pixel_put(glob->mlx_ptr, glob->win_ptr, SCREEN_W / 2,
		SCREEN_H / 2, 0x00FFFFFF);
}
