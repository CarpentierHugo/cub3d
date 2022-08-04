/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <achatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:36:59 by achatela          #+#    #+#             */
/*   Updated: 2022/08/04 15:58:07 by achatela         ###   ########.fr       */
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

static void ft_north_texture(t_glob *glob, char *texture, int j, int length)
{
    int i;

    i = -1;
    glob->n_img->path_texture = malloc(sizeof(char) * length);
    while (++i < length - 1 && texture[j] && texture[j] != ' ')
    {
        glob->n_img->path_texture[i] = texture[j];
        j++;
    }
    glob->n_img->path_texture[i] = '\0';
}

static void ft_path_texture(t_glob *glob, char direction, int j, char *texture)
{
    int len;

    len = j;
    while (texture[len] && texture[len] != ' ')
        len++;
    if (direction == 'N')
        ft_north_texture(glob, texture, j, len - j + 2);
    if (direction == 'S')
        ft_south_texture(glob, texture, j, len - j + 2);
    if (direction == 'W')
        ft_west_texture(glob, texture, j, len - j + 2);
    if (direction == 'E')
        ft_east_texture(glob, texture, j, len - j + 2);
}

void    ft_get_textures(t_glob *glob, int i, int j)
{
    int     count_texture;
    char    direction;

    count_texture = 0;
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
            ft_path_texture(glob, direction, j, glob->map[i] + j);
            count_texture++;
        }
    }
}