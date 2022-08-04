/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <achatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:36:59 by achatela          #+#    #+#             */
/*   Updated: 2022/08/04 18:20:58 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int  check_direction(char first, char second)
{
    if (first == 'N' && second == 'O')
        return (2);
    if (first == 'S' && second == 'O')
        return (2);
    if (first == 'W' && second == 'E')
        return (2);
    if (first == 'E' && second == 'A')
        return (2);
    if (first == 'N')
        return (1);
    if (first == 'S')
        return (1);
    if (first == 'W')
        return (1);
    if (first == 'E')
        return (1);
    return (0);
}

static int ft_north_texture(t_glob *glob, char *texture, int length)
{
    int i;

    if (glob->n_img->path_texture != NULL)
        return (1);
    i = -1;
    glob->n_img->path_texture = malloc(sizeof(char) * length + 10);
    while (texture[++i] && texture[i] != ' ')
    {
        glob->n_img->path_texture[i] = texture[i];
    }
    glob->n_img->path_texture[i] = '\0';
    return (0);
}

static int ft_south_texture(t_glob *glob, char *texture, int length)
{
    int i;

    if (glob->s_img->path_texture != NULL)
        return (1);
    i = -1;
    glob->s_img->path_texture = malloc(sizeof(char) * length);
    while (texture[++i] && texture[i] != ' ')
    {
        glob->s_img->path_texture[i] = texture[i];
    }
    glob->s_img->path_texture[i] = '\0';
    return (0);
}

static int ft_west_texture(t_glob *glob, char *texture, int length)
{
    int i;

    if (glob->w_img->path_texture != NULL)
        return (1);
    i = -1;
    glob->w_img->path_texture = malloc(sizeof(char) * length);
    while (texture[++i] && texture[i] != ' ')
    {
        glob->w_img->path_texture[i] = texture[i];
    }
    glob->w_img->path_texture[i] = '\0';
    return (0);
}

static int ft_east_texture(t_glob *glob, char *texture, int length)
{
    int i;

    if (glob->e_img->path_texture != NULL)
        return (1);
    i = -1;
    glob->e_img->path_texture = malloc(sizeof(char) * length);
    while (texture[++i] && texture[i] != ' ')
    {
        glob->e_img->path_texture[i] = texture[i];
    }
    glob->e_img->path_texture[i] = '\0';
    return (0);
}

static int ft_path_texture(t_glob *glob, char direction, int j, char *texture)
{
    int len;
    int ret;
    
    len = j;
    while (texture[len] && texture[len] != ' ')
        len++;
    if (direction == 'N')
        ret = ft_north_texture(glob, texture, len - j + 4);
    if (direction == 'S')
        ret = ft_south_texture(glob, texture, len - j + 4);
    if (direction == 'W')
        ret = ft_west_texture(glob, texture, len - j + 4);
    if (direction == 'E')
        ret = ft_east_texture(glob, texture, len - j + 4);
    return (ret);
}

void    ft_get_textures(t_glob *glob, int i, int j)
{
    int     count_texture;
    char    direction;

    count_texture = 0;
    glob->n_img->path_texture = NULL;
    glob->s_img->path_texture = NULL;
    glob->w_img->path_texture = NULL;
    glob->e_img->path_texture = NULL;
    while (glob->map[++i][j] && count_texture < 4)
    {
        while (glob->map[i][j] && glob->map[i][j] == ' ')
            j++;
        if (glob->map[i][j] && check_direction(glob->map[i][j], glob->map[i][j + 1]) != 0)
            direction = glob->map[i][j];
        if (glob->map[i][j])
            j += 2;
        while (glob->map[i][j] && glob->map[i][j] == ' ')
            j++;
        if (glob->map[i][j])
        {
            if (ft_path_texture(glob, direction, j, glob->map[i] + j) == 0)
                count_texture++;
            else
                break; //gérer l'erreur (plusieurs texture pour la même direction)
        }
        j = 0;
        direction = '\0';
    }
}