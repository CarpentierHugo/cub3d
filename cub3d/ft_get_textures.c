/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <achatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:36:59 by achatela          #+#    #+#             */
/*   Updated: 2022/08/28 16:47:35 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

static int ft_strlen_custom(char *str)
{
    int i;
    int ret;

    i = 0;
    ret = 0;
    while (str[i])
    {
        if (str[i] == ' ')
            i++;
        else 
        {
            i++;
            ret++;
        }
    }
    return (ret);
}

static int  check_direction(char first, char second)
{
    if (first == 'C' && second == ' ')
        return (2);
    if (first == 'F' && second == ' ')
        return (2);
    if (first == 'N' && second == 'O')
        return (2);
    if (first == 'S' && second == 'O')
        return (2);
    if (first == 'W' && second == 'E')
        return (2);
    if (first == 'E' && second == 'A')
         return (2);
    // if (first == 'N')
    //     return (1);
    // if (first == 'S')
    //     return (1);
    // if (first == 'W')
    //     return (1);
    // if (first == 'E')
    //     return (1);
    return (0);
}

static int ft_north_texture(t_glob *glob, char *texture, int length)
{
    int i;

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

static int ft_south_texture(t_glob *glob, char *texture, int length)
{
    int i;

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

static int ft_west_texture(t_glob *glob, char *texture, int length)
{
    int i;

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

static int ft_east_texture(t_glob *glob, char *texture, int length)
{
    int i;

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

int ft_rgb_error(char **number, int i)
{
    if (number[0] == 0 || number[1] == 0 || number[2] == 0) // fonctionne pas quand number == NULL ou que F ou C est suivi de rien ?
    {
        printf("Error\nRGB Format error (Too few arguments)\n");
        return (1);
    }
    if (number[3] != 0)
    {
        printf("Error\nRGB Format error (Too many arguments)\n");
        return (1);
    }
    if (((number[0][0] != '-' && ft_strlen_custom(number[0]) > 3) || (number[1][0] != '-' && ft_strlen_custom(number[1]) > 3) || (number[2][0] != '-' && ft_strlen_custom(number[2]) > 3))
        || (ft_strlen_custom(number[0]) > 4) || ft_strlen_custom(number[1]) > 4 || ft_strlen_custom(number[2]) > 4)
    {
        printf("Error\nRGB Value contain more than 3 numbers\n");
        return (1);
    }
    if (ft_atoi(number[0]) < 0 || ft_atoi(number[1]) < 0 || ft_atoi(number[2]) < 0)
    {
        printf("Error\nRGB Value is negative\n");
        return (1);
    }
    if (ft_atoi(number[0]) > 255 || ft_atoi(number[1]) > 255 || ft_atoi(number[2]) > 255)
    {
        printf("Error\nRGB Value is higher than 255\n");
        return (1);
    }
    return (0);
}

void    ft_free_number(char **number, int i)
{
    while (number[i] != 0)
    {
        free(number[i]);
        i++;
    }
    free(number);
}

int ft_get_ceiling(t_glob *glob, char *texture, int length)
{
    char **number;

    if (glob->ceiling != -1)
        return (1);
    number = NULL;
    number = ft_split_modif(texture, ',');
    if (number == NULL)
        return (1);
    if (ft_rgb_error(number, 0) == 1)
    {
        ft_free_number(number, 0);
        return (1);
    }
    glob->ceiling = 0;
    glob->ceiling += ft_atoi(number[0]) * 65536;
    glob->ceiling += ft_atoi(number[1]) * 256;
    glob->ceiling += ft_atoi(number[2]);
    ft_free_number(number, 0);
    return (0);
}

int ft_get_floor(t_glob *glob, char *texture, int length)
{
    char **number;

    if (glob->floor != -1)
        return (1);
    number = NULL;
    number = ft_split_modif(texture, ',');
    if (number == NULL)
        return (1);
    if (ft_rgb_error(number, 0) == 1)
    {
        ft_free_number(number, 0);
        return (1);
    }
    glob->floor = 0;
    glob->floor += ft_atoi(number[0]) * 65536;
    glob->floor += ft_atoi(number[1]) * 256;
    glob->floor += ft_atoi(number[2]);
    ft_free_number(number, 0);
    return (0);
}

static int ft_path_texture(t_glob *glob, char direction, int j, char *texture)
{
    int len;
    int ret;
    
    ret = 0;
    len = j;
    if (direction == 'C')
        ret = ft_get_ceiling(glob, texture, 0);
    else if (direction == 'F')
        ret = ft_get_floor(glob, texture, 0);
    else if (direction == 'N')
        ret = ft_north_texture(glob, texture, len - j + 4);
    else if (direction == 'S')
        ret = ft_south_texture(glob, texture, len - j + 4);
    else if (direction == 'W')
        ret = ft_west_texture(glob, texture, len - j + 4);
    else if (direction == 'E')
        ret = ft_east_texture(glob, texture, len - j + 4);
    else
        ret = 1;
    return (ret);
}

int     ft_map_beginning(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '1' || str[i] == '0' || str[i] == 'N'
            || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
            return (1);
        else
            i++;
    }
    return (0);
}

int    ft_get_textures(t_glob *glob, int i, int j)
{
    int     count_texture;
    char    direction = '\0';

    count_texture = 0;
    glob->map_begin = -1;
    glob->n_img->path_texture = NULL;
    glob->s_img->path_texture = NULL;
    glob->w_img->path_texture = NULL;
    glob->e_img->path_texture = NULL;
    while (glob->map[++i][j] && count_texture < 6) // si count_texture == 6 mais qu'il reste des lignes de textures/floor/ceiling à parser il faut pas arrêter la boucle en fait
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
            if (direction != '\0' && ft_path_texture(glob, direction, j, glob->map[i] + j) == 0)
                count_texture++;
            else
                return (1);
        }
        j = 0;
        direction = '\0';
    }
    while (glob->map[i] != 0)
    {
        if (ft_map_beginning(glob->map[i]) == 1)
            break ;
        i++;
    }
    if (glob->map[i] == 0)
    {
        printf("Error\nThere is no map is the file\n");
        return (2);
    }
    glob->map_begin = i;
    return (0);
}