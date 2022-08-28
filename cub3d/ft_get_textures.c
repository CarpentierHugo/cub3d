/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <achatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:36:59 by achatela          #+#    #+#             */
/*   Updated: 2022/08/28 16:01:07 by achatela         ###   ########.fr       */
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
    if (number[0] == 0 || number[1] == 0 || number[2] == 0)
    {
        printf("RGB Format error (Too few arguments)\n");
        return (1);
    }
    if (number[3] != 0)
    {
        printf("RGB Format error (Too many arguments)\n");
        return (1);
    }
    if (((number[0][0] != '-' && ft_strlen(number[0]) > 3) || (number[1][0] != '-' && ft_strlen(number[1]) > 3) || (number[2][0] != '-' && ft_strlen(number[2]) > 3))
        || (ft_strlen(number[0]) > 4) || ft_strlen(number[1]) > 4 || ft_strlen(number[2]) > 4) // strlen custom qui s'arrête aux espaces? ? ? ?
    {
        printf("RGB Value contain more than 3 numbers\n");
        return (1);
    }
    if (ft_atoi(number[0]) < 0 || ft_atoi(number[1]) < 0 || ft_atoi(number[2]) < 0)
    {
        printf("RGB Value is negative\n");
        return (1);
    }
    return (0);
}

int ft_get_ceiling(t_glob *glob, char *texture, int length)
{
    int i;
    char **number;
    /*vérifier que nombre < 255, pas de négatifs, que 3 nombres, rien d'autre sur la ligne*/

    if (glob->ceiling != -1)
        return (1);
    number = ft_split_modif(texture, ',');
    i = 0;
    while (number[i])
    {
        if (ft_strlen(number[i]) > 3)
            printf("Wrong number floor\n");
        i++;
        //break ou return si un nombre est pas dans le bon format
    }
    glob->ceiling = 0;
    glob->ceiling += ft_atoi(number[0]) * 65536;
    glob->ceiling += ft_atoi(number[1]) * 256;
    glob->ceiling += ft_atoi(number[2]);
    return (0);
}

int ft_get_floor(t_glob *glob, char *texture, int length)
{
    int i;
    char **number;
    /*vérifier que nombre < 255, pas de négatifs, que 3 nombres, rien d'autre sur la ligne*/

    if (glob->floor != -1)
        return (1);
    number = ft_split_modif(texture, ',');
    if (ft_rgb_error(number, 0) == 1)
        return (1); // peut-être return 2 pour gérer les erreurs
    i = 0;
    while (number[i])
    {
        if (ft_strlen(number[i]) > 3)
            printf("Wrong number floor\n");
        i++;
        //break ou return si un nombre est pas dans le bon format
    }
    glob->floor = 0;
    glob->floor += ft_atoi(number[0]) * 65536;
    glob->floor += ft_atoi(number[1]) * 256;
    glob->floor += ft_atoi(number[2]);
    return (0);
}

static int ft_path_texture(t_glob *glob, char direction, int j, char *texture)
{
    int len;
    int ret;
    
    ret = 0;
    len = j;
    // while (texture[len] && texture[len] != ' ')
        // len++;
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
    while (glob->map[++i][j] && count_texture < 6) // a changer en 6 pour gerer floor/ceiling)
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
            {
                printf("get texture 1 returned\n");
                return (1);
            }
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
    printf("map begin string: \"%s\"\n", glob->map[i]);
    if (glob->map[i] == 0)
    {
        printf("Pas de map\n");
        return (2);
    }
    /* renvoyer le bon map begin*/
    glob->map_begin = i;
    return (0);
}