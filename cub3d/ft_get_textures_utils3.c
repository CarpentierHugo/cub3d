/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_textures_utils3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <achatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 21:10:28 by achatela          #+#    #+#             */
/*   Updated: 2022/09/08 21:13:10 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_set_to_null(t_glob *glob)
{
	glob->n_img->path_texture = NULL;
	glob->s_img->path_texture = NULL;
	glob->w_img->path_texture = NULL;
	glob->e_img->path_texture = NULL;
	glob->n_img->ptr = NULL;
	glob->s_img->ptr = NULL;
	glob->e_img->ptr = NULL;
	glob->w_img->ptr = NULL;
}
