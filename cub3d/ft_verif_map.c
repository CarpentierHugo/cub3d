/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verif_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <achatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 17:35:51 by achatela          #+#    #+#             */
/*   Updated: 2022/09/08 17:37:04 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void    ft_error_map(int error, t_glob *glob)
{
    printf("Error\n");
    if (error == 0)
        printf("Map contains empty lines\n");
    if (error == 1)
        printf("Map contains an invalid character !\n");
    else if (error == 2)
        printf("Too many starting position in map !\n");
    else if (error == 3)
        printf("Map is not surrounded by walls !\n");
    else if (error == 4)
        printf("Map has no walls\n");
    else if (error == 5)
        printf("Map has no floors\n");
    else if (error == 6)
        printf("Map has no starting position\n");
    ft_free(glob);
    exit(1);
}

static void    ft_check_empty_lines(char **map, t_glob *glob)
{
    int i;
    int j;

    i = -1;
    while (map[++i])
    {
        j = 0;
        while (map[i][j] == ' ')
            j++;
        if (map[i][j] == '\0')
            ft_error_map(0, glob);
    }
}

void    ft_verif_map(char **map, t_glob *glob)
{
    int y;
    int x;
    int isone;
    int iszero;
    int ispos;

    isone = 0;
    iszero = 0;
    ispos = 0;
    y = -1;
    
    ft_check_empty_lines(map, glob);
    while (map[++y])
    {
        x = -1;
        while (map[y][++x])
        {
            if (map[y][x] == '1')
                isone++;
            else if (map[y][x] == '0')
                iszero++;
            else if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E' || map[y][x] == 'W')
            { 
                glob->px = x * SQR_SIZE + SQR_SIZE / 2;
                glob->py = y * SQR_SIZE + SQR_SIZE / 2;
                if (glob->map[y][x] == 'N')
                    glob->pa = 3 * PI / 2;
                if (glob->map[y][x] == 'S')
                    glob->pa = PI / 2;
                if (glob->map[y][x] == 'E')
                    glob->pa = 0;
                if (glob->map[y][x] == 'W')
                    glob->pa = PI;
                ispos++;
                map[y][x] = '0';
            }
            else if (map[y][x] != ' ')
                ft_error_map(1, glob);
            if (ispos > 1)
                ft_error_map(2, glob);
            if (map[y][x] != '1' && map[y][x] != ' ')
            {
                if (!y || !x || !map[y + 1] || map[y - 1][x] == ' ' || !map[y - 1][x] || map[y][x + 1] == ' ' || !map[y][x + 1] || map[y + 1][x] == ' ' || !map[y + 1][x] || map[y][x - 1] == ' ' || !map[y][x - 1])
                    ft_error_map(3, glob);
            }
        }
    }
    if (!isone)
        ft_error_map(4, glob);
    if (!iszero)
        ft_error_map(5, glob);
    if (!ispos)
        ft_error_map(6, glob);
}