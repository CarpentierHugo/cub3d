/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assign_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <achatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 17:59:00 by achatela          #+#    #+#             */
/*   Updated: 2022/09/08 18:00:35 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_north_texture(t_glob *glob, char *texture, int length)
{
	int	i;

	length = 0;
	while (texture[length] != '\0' && texture[length] != ' ')
		length++;
	if (glob->n_img->path_texture != NULL)
		return (1);
	i = -1;
	glob->n_img->path_texture = malloc(sizeof(char) * length + 1);
	while (texture[++i] && texture[i] != ' ')
	{
		glob->n_img->path_texture[i] = texture[i];
	}
	glob->n_img->path_texture[i] = '\0';
	return (0);
}

int	ft_south_texture(t_glob *glob, char *texture, int length)
{
	int	i;

	length = 0;
	while (texture[length] != '\0' && texture[length] != ' ')
		length++;
	if (glob->s_img->path_texture != NULL)
		return (1);
	i = -1;
	glob->s_img->path_texture = malloc(sizeof(char) * length + 1);
	while (texture[++i] && texture[i] != ' ')
	{
		glob->s_img->path_texture[i] = texture[i];
	}
	glob->s_img->path_texture[i] = '\0';
	return (0);
}

int	ft_west_texture(t_glob *glob, char *texture, int length)
{
	int	i;

	length = 0;
	while (texture[length] != '\0' && texture[length] != ' ')
		length++;
	if (glob->w_img->path_texture != NULL)
		return (1);
	i = -1;
	glob->w_img->path_texture = malloc(sizeof(char) * length + 1);
	while (texture[++i] && texture[i] != ' ')
	{
		glob->w_img->path_texture[i] = texture[i];
	}
	glob->w_img->path_texture[i] = '\0';
	return (0);
}

int	ft_east_texture(t_glob *glob, char *texture, int length)
{
	int	i;

	length = 0;
	while (texture[length] != '\0' && texture[length] != ' ')
		length++;
	if (glob->e_img->path_texture != NULL)
		return (1);
	i = -1;
	glob->e_img->path_texture = malloc(sizeof(char) * length + 1);
	while (texture[++i] && texture[i] != ' ')
	{
		glob->e_img->path_texture[i] = texture[i];
	}
	glob->e_img->path_texture[i] = '\0';
	return (0);
}
