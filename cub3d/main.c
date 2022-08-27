/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <achatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 02:16:59 by hcarpent          #+#    #+#             */
/*   Updated: 2022/08/27 15:12:43 by achatela         ###   ########.fr       */
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
    mlx_destroy_image(glob->mlx_ptr, glob->n_img->ptr);
    mlx_destroy_image(glob->mlx_ptr, glob->s_img->ptr);
    mlx_destroy_image(glob->mlx_ptr, glob->e_img->ptr);
    mlx_destroy_image(glob->mlx_ptr, glob->w_img->ptr);
    mlx_destroy_window(glob->mlx_ptr, glob->win_ptr);
	mlx_loop_end(glob->mlx_ptr);
    return (0);
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
        tab[i][j] = '\0';
        str -= j;
        j = 0;
        while (*str != c && *str)
        {
            tab[i][j++] = *str;
            str++;
        }
    }
    tab[i] = 0;
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
/*    while (map[++y])
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
        exit(1);*/
}

void    ft_parsing(char *mapfile, t_glob *glob)
{
    char    *mapstr;
    char    buf;
    int     fd;
    int     size;
    int     i;

    glob->map = NULL;
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
    free(mapstr);
    ft_verif_map(glob->map);
}

void    ft_draw_square(t_glob *glob, int posx, int posy, int color)
{
    int x;
    int y;

    y = -1;
    while (++y < SQR_SIZE)
    {
        x = -1;
        while (++x < SQR_SIZE)
            mlx_pixel_put(glob->mlx_ptr, glob->win_ptr, posx * SQR_SIZE + x, posy * SQR_SIZE + y, color);
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
                if (glob->map[y][x] != '0')
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
                }
            }
        }
    }
}

int get_texture_color(t_glob *glob, float tx, float ty)
{
    if ((glob->pa <= PI / 4 && glob->pa >= 0) || (glob->pa >= 7 * PI / 4 && glob->pa <= 2 * PI))
        return (glob->w_img->data[(int)tx + (int)ty * 32]);
    else if (glob->pa >= 5 * PI / 4 && glob->pa <= 7 * PI / 4)
        return (glob->s_img->data[(int)tx + (int)ty  * 32]);
    else if (glob->pa >= 3 * PI / 4 && glob->pa <= 5 * PI / 4)
        return (glob->e_img->data[(int)tx + (int)ty  * 32]);
    else if (glob->pa >= PI / 4 && glob->pa <= 3 * PI / 4)
        return (glob->n_img->data[(int)tx + (int)ty  * 32]);
    return (0x00000000);
}

void    ft_modelisation(t_glob *glob, int length, int i, float rx, float ry, float ra, int **data)
{
    int     lineh;
    int   lineo;
    int     x;
    int     y;
    float   ty;
    float   tx;
    float   ty_step;
    int     c;
    float   ty_off;
    float   ca;
    int     j;
    int     k;

    ca = glob->pa - ra;
    if (ca < 0)
        ca += 2 * PI;
    if (ca > 2 * PI)
        ca -= 2 * PI;
    length *= cos(ca);
    lineh = SQR_SIZE * SCREEN_H / length * 1.3;
    ty_step = 32 / (float)lineh; //remplacer 32
    ty_off = 0;
    if (lineh > SCREEN_H)
    {
        ty_off = (lineh - SCREEN_H) / 2;
        lineh = SCREEN_H;
    }
    lineo = SCREEN_H / 2 - (lineh / 2);
    ty = ty_off * ty_step;
    y = -1;
    while (++y < lineh)
    {
        x = -1;
        while (++x < 1)
        {
            tx = (int)((rx + ry) / 2) % 32;  //remplacer 32
            c = get_texture_color(glob, tx, ty);
            if ((int)ry % SQR_SIZE == 0)
            {  
                if (glob->map[(int)((ry - 1) / SQR_SIZE)][(int)(rx / SQR_SIZE)] != '1' && (glob->map[(int)(ry / SQR_SIZE)][(int)((rx - 1) / SQR_SIZE)] != '1' || glob->map[(int)(ry / SQR_SIZE)][(int)((rx + 1) / SQR_SIZE)] != '1'))
                {
                    if (&glob->map[(int)((ry - sin(ra)) / SQR_SIZE)][(int)((rx - cos(ra)) / SQR_SIZE)] == &glob->map[(int)((ry - 1) / SQR_SIZE)][(int)(rx / SQR_SIZE)])
                        c = glob->n_img->data[(int)tx + (int)ty  * 32];
                }
                else if (glob->map[(int)((ry - 1) / SQR_SIZE)][(int)(rx / SQR_SIZE)] != '1')
                    c = glob->n_img->data[(int)tx + (int)ty  * 32];
            }   
            if ((int)ry % SQR_SIZE == SQR_SIZE - 1)
            {  
                if (glob->map[(int)((ry + 1) / SQR_SIZE)][(int)(rx / SQR_SIZE)] != '1' && (glob->map[(int)(ry / SQR_SIZE)][(int)((rx - 1) / SQR_SIZE)] != '1' || glob->map[(int)(ry / SQR_SIZE)][(int)((rx + 1) / SQR_SIZE)] != '1'))
                {
                    if (&glob->map[(int)((ry - sin(ra)) / SQR_SIZE)][(int)((rx - cos(ra)) / SQR_SIZE)] == &glob->map[(int)((ry + 1) / SQR_SIZE)][(int)(rx / SQR_SIZE)])
                        c = glob->s_img->data[(int)tx + (int)ty  * 32];
                }
                else if (glob->map[(int)((ry + 1) / SQR_SIZE)][(int)(rx / SQR_SIZE)] != '1')
                    c = glob->s_img->data[(int)tx + (int)ty  * 32];
            }
            if ((int)rx % SQR_SIZE == SQR_SIZE - 1)
            {  
                if (glob->map[(int)(ry / SQR_SIZE)][(int)((rx + 1) / SQR_SIZE)] != '1' && (glob->map[(int)((ry - 1) / SQR_SIZE)][(int)(rx / SQR_SIZE)] != '1' || glob->map[(int)((ry + 1) / SQR_SIZE)][(int)(rx / SQR_SIZE)] != '1'))
                {
                    if (&glob->map[(int)((ry - sin(ra)) / SQR_SIZE)][(int)((rx - cos(ra)) / SQR_SIZE)] == &glob->map[(int)(ry / SQR_SIZE)][(int)((rx + 1) / SQR_SIZE)])
                        c = glob->e_img->data[(int)tx + (int)ty  * 32];
                }
                else if (glob->map[(int)(ry / SQR_SIZE)][(int)((rx + 1) / SQR_SIZE)] != '1')
                    c = glob->e_img->data[(int)tx + (int)ty  * 32];
            }
            if ((int)rx % SQR_SIZE == 0)
            {  
                if (glob->map[(int)(ry / SQR_SIZE)][(int)((rx - 1) / SQR_SIZE)] != '1' && (glob->map[(int)((ry - 1) / SQR_SIZE)][(int)(rx / SQR_SIZE)] != '1' || glob->map[(int)((ry + 1) / SQR_SIZE)][(int)(rx / SQR_SIZE)] != '1'))
                {
                    if (&glob->map[(int)((ry - sin(ra)) / SQR_SIZE)][(int)((rx - cos(ra)) / SQR_SIZE)] == &glob->map[(int)(ry / SQR_SIZE)][(int)((rx - 1) / SQR_SIZE)])
                        c = glob->w_img->data[(int)tx + (int)ty  * 32];
                }
                else if (glob->map[(int)(ry / SQR_SIZE)][(int)((rx - 1) / SQR_SIZE)] != '1')
                    c = glob->w_img->data[(int)tx + (int)ty  * 32];
            }
            data[0][(int)(((i * 1 + x) + ((y + (int)lineo) * (SCREEN_W))))] = c;
            ty += ty_step;
        }
    }
    j = -1;
    while (++j < lineo)
    {
        k = -1;
        while (++k < 1)
            data[0][(int)((i * 1 + k) + (j * (SCREEN_W)))] = 0x00FFFFFF;
    }
    j = lineo + lineh - 1;
    while (++j < SCREEN_H)
    {
        k = -1;
        while (++k < 1)
            data[0][(int)((i * 1 + k) + (j * (SCREEN_W)))] = 0x00CDCDCD;
    }
}

void    ft_move(t_glob *glob, int key)
{
    if (key == Z)
    {
        glob->px += cos(glob->pa) * MOV_SPD;
        glob->py += sin(glob->pa) * MOV_SPD;
    }
    if (key == Q)
    {
        glob->px += sin(glob->pa) * MOV_SPD;
        glob->py -= cos(glob->pa) * MOV_SPD;
    }
    if (key == S)
    {
        glob->px -= cos(glob->pa) * MOV_SPD;
        glob->py -= sin(glob->pa) * MOV_SPD;
    }
    if (key == D)
    {
        glob->px -= sin(glob->pa) * MOV_SPD;
        glob->py += cos(glob->pa) * MOV_SPD;
    }
    if (key == L_ARROW)
    {
        glob->pa -= ROT_SPD;
        if (glob->pa < 0)
            glob->pa += 2 * PI;
    }
    if (key == R_ARROW)
    {
        glob->pa += ROT_SPD;
        if (glob->pa > 2 * PI)
            glob->pa -= 2 * PI;
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
    while (++i < FOV * 3 * 8)
    {
        x = glob.px;
        y = glob.py;
        length = 0;
        while (glob.map[(int)(y / SQR_SIZE)][(int)(x / SQR_SIZE)] != '1')
        {
            x += cos(ra);
            y += sin(ra);
            length++;
        }
        if (length <= 1)
            return (1);
        ra += DR / 3 / 8;
    }
    return (0);
}

void    ft_raycasting(t_glob *glob)
{
    float   rx;
    float   ry;
    float   ra;
    int     length;
    int     i;
    void    *image;
    int     *data;

    image = mlx_new_image(glob->mlx_ptr, SCREEN_W, SCREEN_H);
    data = (int *)mlx_get_data_addr(image, &glob->s_img->bpp, &glob->s_img->sl, &glob->s_img->e);
    ra = glob->pa - DR * (FOV / 2);
    i = -1;
    while (++i < FOV * 3 * 8)
    {
        rx = glob->px;
        ry = glob->py;
        length = 0;
        while (glob->map[(int)(ry / SQR_SIZE)][(int)(rx / SQR_SIZE)] != '1')
        {
            rx += cos(ra);
            ry += sin(ra);
            length++;
        }
        ft_modelisation(glob, length, i, rx, ry, ra, &data);
        ra += (DR / 3 / 8);
    }
    mlx_put_image_to_window (glob->mlx_ptr, glob->win_ptr, image, 0, 0);
    mlx_destroy_image(glob->mlx_ptr, image);
}

int ft_deal_key(int key, void *param)
{
    t_glob *glob;

    glob = (t_glob *)param;
    if (key == Z || key == Q || key == S || key == D || key == L_ARROW || key == R_ARROW)
    {
        //ft_draw_player(glob, 8, 0x00CDCDCD);
        if (!ft_raytesting(*glob, key))
            ft_move(glob, key);
        //ft_draw_player(glob, 8, 0x00FFFF00);
        ft_raycasting(glob);
    }
    if (key == ESC)
        ft_exit(glob);
    return (0);
}

void    ft_init_img(t_glob *glob)
{
    glob->n_img->h = 32;
    glob->n_img->w = 32;
    glob->n_img->bpp = 8;
    glob->n_img->sl = 8 * 32;
    glob->n_img->e = 0;
    glob->s_img->h = 32;
    glob->s_img->w = 32;
    glob->s_img->bpp = 8;
    glob->s_img->sl = 8 * 32;
    glob->s_img->e = 0;
    glob->w_img->h = 32;
    glob->w_img->w = 32;
    glob->w_img->bpp = 8;
    glob->w_img->sl = 8 * 32;
    glob->w_img->e = 0;
    glob->e_img->h = 32;
    glob->e_img->w = 32;
    glob->e_img->bpp = 8;
    glob->e_img->sl = 8 * 32;
    glob->e_img->e = 0;
}

void    ft_screen_test(t_glob *glob)
{
    ft_init_img(glob);
    glob->n_img->ptr = mlx_xpm_file_to_image(glob->mlx_ptr, glob->n_img->path_texture, &glob->n_img->w, &glob->n_img->h);
    glob->n_img->data = (int *)mlx_get_data_addr(glob->n_img->ptr, &glob->n_img->bpp, &glob->n_img->sl, &glob->n_img->e);
    glob->s_img->ptr = mlx_xpm_file_to_image(glob->mlx_ptr, glob->s_img->path_texture, &glob->s_img->w, &glob->s_img->h); // sus glob->s_img->path_texture ??
    glob->s_img->data = (int *)mlx_get_data_addr(glob->s_img->ptr, &glob->s_img->bpp, &glob->s_img->sl, &glob->s_img->e);
    glob->e_img->ptr = mlx_xpm_file_to_image(glob->mlx_ptr, glob->e_img->path_texture, &glob->e_img->w, &glob->e_img->h);
    glob->e_img->data = (int *)mlx_get_data_addr(glob->e_img->ptr, &glob->e_img->bpp, &glob->e_img->sl, &glob->e_img->e);
    glob->w_img->ptr = mlx_xpm_file_to_image(glob->mlx_ptr, glob->w_img->path_texture, &glob->w_img->w, &glob->w_img->h);
    glob->w_img->data = (int *)mlx_get_data_addr(glob->w_img->ptr, &glob->w_img->bpp, &glob->w_img->sl, &glob->w_img->e);
}

int main(int argc, char **argv)
{
    t_glob   glob[1];

    if (argc != 2)
        return (1);
    ft_parsing(argv[1], glob);
    glob->ceiling = -1;
    glob->floor = -1;
    if (ft_get_textures(glob, -1, 0) == 1)
    {
        printf("Error (erreur a developper)\n");
        return (1);
    }
    if (glob->s_img->path_texture == NULL)
        printf("Faut gérer quand y a trop de texture SUU\n");
    glob->mlx_ptr = mlx_init();
	if (!glob->mlx_ptr)
		return (1);
	glob->win_ptr = mlx_new_window(glob->mlx_ptr, SCREEN_W, SCREEN_H, "cub3d");
    ft_draw_map(glob);
    //ft_draw_player(glob, 8, 0x00FFFF00);
    ft_screen_test(glob);
    ft_raycasting(glob);
    mlx_hook(glob->win_ptr, 2, (1L<<0), &ft_deal_key, glob);
    mlx_hook(glob->win_ptr, 17, 0, &ft_exit, glob);
    mlx_loop(glob->mlx_ptr);
    mlx_destroy_display(glob->mlx_ptr);
    free(glob->mlx_ptr);
    return (0);
}
