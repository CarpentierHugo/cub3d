/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <achatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:51:36 by achatela          #+#    #+#             */
/*   Updated: 2022/08/29 19:46:49 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    ft_draw_square(t_glob *glob, int posx, int posy, int color)
{
    int x;
    int y;

    y = -1;
    while (++y < SCREEN_H / 8 / 5)
    {
        x = -1;
        while (++x < SCREEN_H / 8 / 5)
            mlx_pixel_put(glob->mlx_ptr, glob->win_ptr, posx + x, posy + y, color);
    }
}

static int ft_strlen(char *str)
{
    int i;
    i = 0;

    while (str[i])
        i++;
    return (i);
}

void    first_line(t_glob *glob, int test)
{
    int i;
    int j;
    int scale;

    scale = 0;
    j = -2;
    i = 0;
    while (i < 5)
    {
        if (((int)(glob->py / SQR_SIZE) - 2) < 0 || (int)((glob->px / SQR_SIZE) + j) < 0 || (int)((glob->px / SQR_SIZE) + j) > ft_strlen(glob->map[(int)((glob->py / SQR_SIZE) - 2)]))
            ft_draw_square(glob, scale, 0, 1641562); // violet
        else if (glob->map[(int)(glob->py / SQR_SIZE) - 2][(int)(glob->px / SQR_SIZE) + j] == '1')
            ft_draw_square(glob, scale, 0, 16000000); // rouge
        else if (glob->map[(int)(glob->py / SQR_SIZE) - 2][(int)(glob->px / SQR_SIZE) + j] == '0' || glob->map[(int)(glob->py / SQR_SIZE) - 2][(int)(glob->px / SQR_SIZE) + j] == 'N')
            ft_draw_square(glob, scale, 0, 1669722); // vert bizzare
        else //if (glob->map[(int)(glob->py / SQR_SIZE) - 2][(int)glob->px / SQR_SIZE] == ' ' || glob->map[(int)(glob->py / SQR_SIZE) - j][(int)glob->px / SQR_SIZE] == '\0')
            ft_draw_square(glob, scale, 0, 0);
        printf("%c", glob->map[(int)(glob->py / SQR_SIZE) - 2][(int)(glob->px  / SQR_SIZE) + j]);
        i++;
        j++;
        scale += test;
    }
    printf("\n");
}

void    second_line(t_glob *glob, int test)
{
    int i;
    int j;
    int scale;
    int scale_fix;

    scale_fix = test;
    scale = 0;
    j = -2;
    i = 0;
    while (i < 5)
    {
        if (((int)(glob->py / SQR_SIZE) - 1) < 0 || (int)((glob->px / SQR_SIZE) + j) < 0 || (int)((glob->px / SQR_SIZE) + j) > ft_strlen(glob->map[(int)((glob->py / SQR_SIZE) - 1)]))
            ft_draw_square(glob, scale, scale_fix, 1641562); // violet
        else if (glob->map[(int)(glob->py / SQR_SIZE) - 1][(int)(glob->px / SQR_SIZE) + j] == '1')
            ft_draw_square(glob, scale, scale_fix, 16000000); // rouge
        else if (glob->map[(int)(glob->py / SQR_SIZE) - 1][(int)(glob->px / SQR_SIZE) + j] == '0' || glob->map[(int)(glob->py / SQR_SIZE) - 1][(int)(glob->px / SQR_SIZE) + j] == 'N')
            ft_draw_square(glob, scale, scale_fix, 1669722); // vert bizzare
        else //if (glob->map[(int)(glob->py / SQR_SIZE) - 2][(int)glob->px / SQR_SIZE] == ' ' || glob->map[(int)(glob->py / SQR_SIZE) - j][(int)glob->px / SQR_SIZE] == '\0')
            ft_draw_square(glob, scale, scale_fix, 0);
        printf("%c", glob->map[(int)(glob->py / SQR_SIZE) - 1][(int)(glob->px  / SQR_SIZE) + j]);
        i++;
        j++;
        scale += test;
    }
    printf("\n");
}

void    third_line(t_glob *glob, int test)
{
    int i;
    int j;
    int scale;
    int scale_fix;

    scale_fix = test * 2;
    scale = 0;
    j = -2;
    i = 0;
    while (i < 5)
    {
        if (((int)(glob->py / SQR_SIZE)) < 0 || (int)((glob->px / SQR_SIZE) + j) < 0 || (int)((glob->px / SQR_SIZE) + j) > ft_strlen(glob->map[(int)((glob->py / SQR_SIZE))]))
            ft_draw_square(glob, scale, scale_fix, 1641562); // violet
        else if (glob->map[(int)(glob->py / SQR_SIZE)][(int)(glob->px / SQR_SIZE) + j] == '1')
            ft_draw_square(glob, scale, scale_fix, 16000000); // rouge
        else if (glob->map[(int)(glob->py / SQR_SIZE)][(int)(glob->px / SQR_SIZE) + j] == '0' || glob->map[(int)(glob->py / SQR_SIZE)][(int)(glob->px / SQR_SIZE) + j] == 'N')
            ft_draw_square(glob, scale, scale_fix, 1669722); // vert bizzare
        else //if (glob->map[(int)(glob->py / SQR_SIZE) - 2][(int)glob->px / SQR_SIZE] == ' ' || glob->map[(int)(glob->py / SQR_SIZE) - j][(int)glob->px / SQR_SIZE] == '\0')
            ft_draw_square(glob, scale, scale_fix, 0);
        printf("%c", glob->map[(int)(glob->py / SQR_SIZE)][(int)(glob->px  / SQR_SIZE) + j]);
        i++;
        j++;
        scale += test;
    }
    printf("\n");
}

void    forth_line(t_glob *glob, int test, int k)
{
    int i;
    int j;
    int scale;
    int scale_fix;

    scale_fix = test * 3;
    scale = 0;
    j = -2;
    i = 0;
    while (i < 5)
    {
        if (((int)(glob->py / SQR_SIZE) + 1) < k - k || (int)((glob->px / SQR_SIZE) + j) < 0 )//|| (int)((glob->px / SQR_SIZE) + j) > ft_strlen(glob->map[(int)((glob->py / SQR_SIZE) + 1)]))
            ft_draw_square(glob, scale, scale_fix, 1641562); // violet
        else if (glob->map[(int)(glob->py / SQR_SIZE) + 1][(int)(glob->px / SQR_SIZE) + j] == '1')
            ft_draw_square(glob, scale, scale_fix, 16000000); // rouge
        else if (glob->map[(int)(glob->py / SQR_SIZE) + 1][(int)(glob->px / SQR_SIZE) + j] == '0' || glob->map[(int)(glob->py / SQR_SIZE) + 1][(int)(glob->px / SQR_SIZE) + j] == 'N')
            ft_draw_square(glob, scale, scale_fix, 1669722); // vert bizzare
        else //if (glob->map[(int)(glob->py / SQR_SIZE) - 2][(int)glob->px / SQR_SIZE] == ' ' || glob->map[(int)(glob->py / SQR_SIZE) - j][(int)glob->px / SQR_SIZE] == '\0')
            ft_draw_square(glob, scale, scale_fix, 0);
        printf("%c", glob->map[(int)(glob->py / SQR_SIZE) + 1][(int)(glob->px  / SQR_SIZE) + j]);
        i++;
        j++;
        scale += test;
    }
    printf("\n");
}

void    fifth_line(t_glob *glob, int test, int k)
{
    int i;
    int j;
    int scale;
    int scale_fix;

    scale_fix = test * 4;
    scale = 0;
    j = -2;
    i = 0;
    while (i < 5)
    {
        if (((int)(glob->py / SQR_SIZE) + 2) < k - k|| (int)((glob->px / SQR_SIZE) + j) < 0 )//|| (int)((glob->px / SQR_SIZE) + j) > ft_strlen(glob->map[(int)((glob->py / SQR_SIZE) + 2)]))
            ft_draw_square(glob, scale, scale_fix, 1641562); // violet
        else if (glob->map[(int)(glob->py / SQR_SIZE) + 2][(int)(glob->px / SQR_SIZE) + j] == '1')
            ft_draw_square(glob, scale, scale_fix, 16000000); // rouge
        else if (glob->map[(int)(glob->py / SQR_SIZE) + 2][(int)(glob->px / SQR_SIZE) + j] == '0' || glob->map[(int)(glob->py / SQR_SIZE) + 2][(int)(glob->px / SQR_SIZE) + j] == 'N')
            ft_draw_square(glob, scale, scale_fix, 1669722); // vert bizzare
        else //if (glob->map[(int)(glob->py / SQR_SIZE) - 2][(int)glob->px / SQR_SIZE] == ' ' || glob->map[(int)(glob->py / SQR_SIZE) - j][(int)glob->px / SQR_SIZE] == '\0')
            ft_draw_square(glob, scale, scale_fix, 0);
        printf("%c", glob->map[(int)(glob->py / SQR_SIZE) + 2][(int)(glob->px  / SQR_SIZE) + j]);
        i++;
        j++;
        scale += test;
    }
    printf("\n");
}

void ft_minimap(t_glob *glob)
{
    int i;

    i = 0;
    while (glob->map[i] != 0)
        i++;
    first_line(glob, SCREEN_H / 8 / 5);
    second_line(glob, SCREEN_H / 8 / 5);
    third_line(glob, SCREEN_H / 8 / 5);
    forth_line(glob, SCREEN_H / 8 / 5, i);
    fifth_line(glob, SCREEN_H / 8 / 5, i);
  /*  if (((int)(glob->py / SQR_SIZE) - 1) == -1 || glob->map[(int)(glob->py / SQR_SIZE) - 1][(int)glob->px / SQR_SIZE] != '1')
        ft_draw_square(glob, 0, 0, 16000000);
    else if (glob->map[(int)(glob->py / SQR_SIZE) - 1][(int)glob->px / SQR_SIZE] != '0')
        ft_draw_square(glob, 0, 0, glob->floor);
    else if (glob->map[(int)(glob->py / SQR_SIZE) - 1][(int)glob->px / SQR_SIZE] != ' ' || glob->map[(int)(glob->py / SQR_SIZE) - 1][(int)glob->px / SQR_SIZE] != '\0')
        ft_draw_square(glob, 0, 0, 0);*/
    return ;
}