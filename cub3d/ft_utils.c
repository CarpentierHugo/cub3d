/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <achatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 19:40:15 by achatela          #+#    #+#             */
/*   Updated: 2022/09/08 19:55:13 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_exit(t_glob *glob)
{
	if (glob->n_img->ptr != NULL)
		mlx_destroy_image(glob->mlx_ptr, glob->n_img->ptr);
	if (glob->s_img->ptr != NULL)
		mlx_destroy_image(glob->mlx_ptr, glob->s_img->ptr);
	if (glob->e_img->ptr != NULL)
		mlx_destroy_image(glob->mlx_ptr, glob->e_img->ptr);
	if (glob->w_img->ptr != NULL)
		mlx_destroy_image(glob->mlx_ptr, glob->w_img->ptr);
	glob->n_img->ptr = NULL;
	glob->s_img->ptr = NULL;
	glob->e_img->ptr = NULL;
	glob->w_img->ptr = NULL;
	mlx_loop_end(glob->mlx_ptr);
	return (0);
}

static int	ft_screen2(t_glob *glob)
{
	glob->s_img->data = (int *)mlx_get_data_addr(glob->s_img->ptr,
			&glob->s_img->bpp, &glob->s_img->sl, &glob->s_img->e);
	glob->e_img->ptr = mlx_xpm_file_to_image(glob->mlx_ptr,
			glob->e_img->path_texture, &glob->e_img->w, &glob->e_img->h);
	if (glob->e_img->ptr == NULL)
		return (1);
	glob->e_img->data = (int *)mlx_get_data_addr(glob->e_img->ptr,
			&glob->e_img->bpp, &glob->e_img->sl, &glob->e_img->e);
	glob->w_img->ptr = mlx_xpm_file_to_image(glob->mlx_ptr,
			glob->w_img->path_texture, &glob->w_img->w, &glob->w_img->h);
	if (glob->w_img->ptr == NULL)
		return (1);
	glob->w_img->data = (int *)mlx_get_data_addr(glob->w_img->ptr,
			&glob->w_img->bpp, &glob->w_img->sl, &glob->w_img->e);
	return (0);
}

static void	ft_init_img(t_glob *glob)
{
	glob->n_img->h = RES;
	glob->n_img->w = RES;
	glob->n_img->bpp = 8;
	glob->n_img->sl = 8 * RES;
	glob->n_img->e = 0;
	glob->s_img->h = RES;
	glob->s_img->w = RES;
	glob->s_img->bpp = 8;
	glob->s_img->sl = 8 * RES;
	glob->s_img->e = 0;
	glob->w_img->h = RES;
	glob->w_img->w = RES;
	glob->w_img->bpp = 8;
	glob->w_img->sl = 8 * RES;
	glob->w_img->e = 0;
	glob->e_img->h = RES;
	glob->e_img->w = RES;
	glob->e_img->bpp = 8;
	glob->e_img->sl = 8 * RES;
	glob->e_img->e = 0;
}

int	ft_screen(t_glob *glob)
{
	ft_init_img(glob);
	glob->n_img->ptr = mlx_xpm_file_to_image(glob->mlx_ptr,
			glob->n_img->path_texture, &glob->n_img->w, &glob->n_img->h);
	if (glob->n_img->ptr == NULL)
		return (1);
	glob->n_img->data = (int *)mlx_get_data_addr(glob->n_img->ptr,
			&glob->n_img->bpp, &glob->n_img->sl, &glob->n_img->e);
	glob->s_img->ptr = mlx_xpm_file_to_image(glob->mlx_ptr,
			glob->s_img->path_texture, &glob->s_img->w, &glob->s_img->h);
	if (glob->s_img->ptr == NULL)
		return (1);
	if (ft_screen2(glob) == 1)
		return (1);
	return (0);
}

int	ft_mouse(int button, int x, int y, void *param)
{
	t_glob	*glob;

	(void)y;
	glob = (t_glob *)param;
	if (button == 1)
	{
		glob->pa += (x - SCREEN_W / 2) * (DR * FOV / SCREEN_W);
		if (glob->pa < 0)
			glob->pa += 2 * PI;
		else if (glob->pa > 2 * PI)
			glob->pa -= 2 * PI;
		ft_raycasting(glob);
	}
	if (glob->minimap == 1)
	{
		ft_raycasting(glob);
		ft_minimap(glob);
	}
	return (0);
}
