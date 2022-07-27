/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarpent <hcarpent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 02:16:59 by hcarpent          #+#    #+#             */
/*   Updated: 2022/07/27 02:57:42 by hcarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    ft_free_map(t_glob *glob)
{
    int i;

    i = 0;
    while (glob->map[i])
        free(glob->map[i++]);
    free(glob->map);
}

int ft_exit(t_glob *glob)
{
    ft_free_map(glob);
    exit (0);
}

int ft_count_words(char *str, char c)
{
    int nbword;

    nbword = 0;
    while (*str)
    {
        while (*str == c)
            str++;
        while (*str != c && *str)
            str++;
        while (*str == c)
            str++;
        nbword++;
    }
    return (nbword);
}

char    **ft_split_modif(char *str, char c)
{
    char    **tab;
    int     nbword;
    int     i;
    int     j;

    nbword = ft_count_words(str, c);
    tab = malloc(sizeof(char *) * (nbword + 1));
    if (!tab)
        return (NULL);
    tab[nbword] = NULL;
    i = -1;
    while (++i < nbword)
    {
        j = 0;
        while (*str == c)
            str++;
        while (*str != c && *str)
        {
            j++;
            str++;
        }
        tab[i] = malloc(sizeof(char) * (j + 1));
        if (!tab[i])
            return (NULL);
        str -= j;
        j = 0;
        while (*str != c && *str)
        {
            tab[i][j++] = *str;
            str++;
        }
    }
    return (tab);
}

void    ft_verif_map(char **map)
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
                ispos++;
            else if (map[y][x] != ' ')
                exit(1);
            if (ispos > 1)
                exit(1);
            if (map[y][x] != '1')
            {
                if (!y || !x)
                    exit(1);
                if (map[y - 1][x] == ' ' || map[y - 1][x + 1] == ' ' || map[y - 1][x + 1] == 0 || map[y][x + 1] == ' ' || map[y][x + 1] == 0 || map[y + 1][x + 1] == ' ' || map[y + 1][x + 1] == 0 || map[y + 1][x] == ' ' || map[y + 1][x] == 0 || map[y + 1][x - 1]  == ' ' || map[y + 1][x - 1]  == 0 || map[y][x - 1] == ' ' || map[y - 1][x - 1] == ' ')
                    exit(1);
            }
        }
    }
    if (!isone || !iszero || !ispos)
        exit(1);
}

void    ft_parsing(char *mapfile, t_glob *glob)
{
    char    *mapstr;
    char    buf;
    int     fd;
    int     size;
    int     i;

    i = 0;
    while (mapfile[i])
        i++;
    if (mapfile[i - 4] != '.' || mapfile[i - 3] != 'c' || mapfile[i - 2] != 'u' || mapfile[i - 1] != 'b')
        exit(1);
    fd = open(mapfile, O_RDONLY);
    if (fd < 0 || fd > 1024 || read(fd, &buf, 0) < 0)
		exit(1);
    size = 0;
    while (read(fd, &buf, 1))
        size++;
    close(fd);
    mapstr = malloc(sizeof(char) * (size + 1));
    if (!mapstr)
        exit(1);
    mapstr[size] = '\0';
    fd = open(mapfile, O_RDONLY);
    if (fd < 0 || fd > 1024 || read(fd, &buf, 0) < 0)
		exit(1);
    read(fd, mapstr, size);
    close(fd);
    glob->map = ft_split_modif(mapstr, '\n');
    ft_verif_map(glob->map);
}

void    ft_draw_square(t_glob *glob, int posx, int posy, int color)
{
    int x;
    int y;

    y = -1;
    while (++y < RES)
    {
        x = -1;
        while (++x < RES)
            mlx_pixel_put(glob->mlx_ptr, glob->win_ptr, posx * RES + x, posy * RES + y, color);
    }
}

void    ft_draw_player(t_glob *glob, int size, int color)
{
    int tmpy;
    int tmpx;

    tmpy = glob->py;
    tmpx = glob->px;
    while (glob->py - tmpy < size)
    {
        while (glob->px - tmpx < size)
        {
            mlx_pixel_put(glob->mlx_ptr, glob->win_ptr, glob->px - size/2, glob->py - size/2, color);
            glob->px++;
        }
        glob->px = tmpx;
        glob->py++;
    }
    glob->py = tmpy;
}

void    ft_draw_map(t_glob *glob)
{
    int x;
    int y;

    y = -1;
    while (glob->map[++y])
    {
        x = -1;
        while (glob->map[y][++x])
        {
            if (glob->map[y][x] == '1')
            {
                //ft_draw_square(glob, x, y, 0x00FFFFFF);
                x += 0;
            }
            else
            {
                //ft_draw_square(glob, x, y, 0x00CDCDCD);
                if (glob->map[y][x] != '0' )
                {
                    glob->px = x * RES + RES/2;
                    glob->py = y * RES + RES/2;
                    if (glob->map[y][x] == 'N')
                        glob->pa = 3 * PI / 2;
                    if (glob->map[y][x] == 'S')
                        glob->pa = PI/2;
                    if (glob->map[y][x] == 'E')
                        glob->pa = 0;
                    if (glob->map[y][x] == 'W')
                        glob->pa = PI;
                    glob->pdx = cos(glob->pa) * MOV_SPD;
                    glob->pdy = sin(glob->pa) * MOV_SPD;
                }
            }
        }
    }
}

void    ft_modelisation(t_glob *glob, float ca, int length, int i, int color)
{
    float   lineh;
    float   lineo;
    int     x;
    int     y;

    if (ca < 0)
        ca += 2 * PI;
    if (ca > 2 * PI)
        ca -= 2 * PI;
    length *= cos(ca);
    lineh = RES * 320 / length;
    if (lineh > 320)
        lineh = 320;
    lineo = 160 - lineh/2;
    y = -1;
    while (++y < lineh)
    {
        x = -1;
        while (++x < 8)
            mlx_pixel_put(glob->mlx_ptr, glob->win_ptr, x + i * 8, y + lineo, color);
    }
}

void    ft_background(t_glob *glob)
{
    int x;
    int y;

    y = -1;
    while (++y < 320)
    {
        x = -1;
        while (++x < 8 * FOV)
        {
            if (y <= 160)
                mlx_pixel_put(glob->mlx_ptr, glob->win_ptr, x, y, 0x000000FF);
            else
                mlx_pixel_put(glob->mlx_ptr, glob->win_ptr, x, y, 0x008B4513);
        }
    }
}

void    ft_move(t_glob *glob, int key)
{
    if (key == Z)
    {
        glob->px += glob->pdx;
        glob->py += glob->pdy;
    }
    if (key == Q)
    {
        glob->pa -= ROT_SPD;
        if (glob->pa < 0)
            glob->pa += 2 * PI;
        glob->pdx = cos(glob->pa) * MOV_SPD;
        glob->pdy = sin(glob->pa) * MOV_SPD;
    }
    if (key == S)
    {
        glob->px -= glob->pdx;
        glob->py -= glob->pdy;
    }
    if (key == D)
    {
        glob->pa += ROT_SPD;
        if (glob->pa > 2 * PI)
            glob->pa -= 2 * PI;
        glob->pdx = cos(glob->pa) * MOV_SPD;
        glob->pdy = sin(glob->pa) * MOV_SPD;
    }
}

int ft_raytesting(t_glob glob, int key)
{
    float   ra;
    int     length;
    int     i;
    float   x;
    float   y;

    ft_move(&glob, key);
    ra = glob.pa - (PI / 180) * (FOV / 2);
    i = -1;
    while (++i < FOV)
    {
        x = glob.px;
        y = glob.py;
        length = 0;
        while (glob.map[(int)(y / RES)][(int)(x / RES)] != '1')
        {
            x += cos(ra);
            y += sin(ra);
            length++;
        }
        if (length <= 4)
            return (1);
        ra += PI / 180;
    }
    return (0);
}

void    ft_raycasting(t_glob *glob, int color)
{
    float   x;
    float   y;
    float   ra;
    int     length;
    int     i;

    ft_background(glob);
    ra = glob->pa - (PI / 180) * (FOV / 2);
    i = -1;
    while (++i < FOV)
    {
        x = glob->px;
        y = glob->py;
        length = 0;
        while (glob->map[(int)(y / RES)][(int)(x / RES)] != '1')
        {
            //mlx_pixel_put(glob->mlx_ptr, glob->win_ptr, x, y, color);
            x += cos(ra);
            y += sin(ra);
            length++;
        }
        ft_modelisation(glob, glob->pa - ra, length, i, color);
        ra += PI / 180;
    }
}

int ft_deal_key(int key, t_glob *glob)
{
   if (key == Z || key == Q || key == S || key == D)
    {
        //ft_draw_player(glob, 8, 0x00CDCDCD);
        if (!ft_raytesting(*glob, key))
            ft_move(glob, key);
        //ft_draw_player(glob, 8, 0x00FFFF00);
        ft_raycasting(glob, 0x00CDCDCD);
    }
    if (key == 53)
        ft_exit(glob);
    return (0);
}

int main(int argc, char **argv)
{
    t_glob   glob[1];

    if (argc != 2)
        return (1);
    ft_parsing(argv[1], glob);
    glob->mlx_ptr = mlx_init();
	if (!glob->mlx_ptr)
		return (1);
	glob->win_ptr = mlx_new_window(glob->mlx_ptr, 1024, 512, "cub3d");
    ft_draw_map(glob);
    //ft_draw_player(glob, 8, 0x00FFFF00);
    ft_raycasting(glob, 0x00CDCDCD);
    mlx_hook(glob->win_ptr, 2, 0, ft_deal_key, glob);
    mlx_hook(glob->win_ptr, 17, 0, ft_exit, glob);
    mlx_loop(glob->mlx_ptr);
    return (0);
}