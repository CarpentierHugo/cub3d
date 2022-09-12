/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <achatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 17:34:39 by achatela          #+#    #+#             */
/*   Updated: 2022/09/08 21:56:09 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free2(t_glob *glob)
{
	if (glob->s_img->path_texture != NULL)
	{
		if (glob->s_img->ptr != NULL)
			mlx_destroy_image(glob->mlx_ptr, glob->s_img->ptr);
		free(glob->s_img->path_texture);
	}
	if (glob->e_img->path_texture != NULL)
	{
		if (glob->e_img->ptr != NULL)
			mlx_destroy_image(glob->mlx_ptr, glob->e_img->ptr);
		free(glob->e_img->path_texture);
	}
	if (glob->w_img->path_texture != NULL)
	{
		if (glob->w_img->ptr != NULL)
			mlx_destroy_image(glob->mlx_ptr, glob->w_img->ptr);
		free(glob->w_img->path_texture);
	}
}

void	ft_free(t_glob *glob)
{
	int	i;

	i = 0;
	while (glob->free_map[i] != 0)
	{
		free(glob->free_map[i]);
		i++;
	}
	free(glob->free_map);
	if (glob->n_img->path_texture != NULL)
	{
		if (glob->n_img->ptr != NULL)
			mlx_destroy_image(glob->mlx_ptr, glob->n_img->ptr);
		free(glob->n_img->path_texture);
	}
	ft_free2(glob);
}
