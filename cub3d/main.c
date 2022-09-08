/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <achatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 02:16:59 by hcarpent          #+#    #+#             */
/*   Updated: 2022/09/08 18:51:57 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_exit(t_glob *glob)
{
    if (glob->n_img->ptr != NULL)
        mlx_destroy_image(glob->mlx_ptr, glob->n_img->ptr);
    if (glob->s_img->ptr != NULL)
        mlx_destroy_image(glob->mlx_ptr, glob->s_img->ptr);
    if (glob->e_img->ptr != NULL)
        mlx_destroy_image(glob->mlx_ptr, glob->e_img->ptr);
    if (glob->w_img->ptr != NULL)
        mlx_destroy_image(glob->mlx_ptr, glob->w_img->ptr);
    glob->n_img->ptr = NULL;
    glob->s_img->ptr = NULL;
    glob->e_img->ptr = NULL;
    glob->w_img->ptr = NULL;
   // mlx_destroy_window(glob->mlx_ptr, glob->win_ptr);
	mlx_loop_end(glob->mlx_ptr);
    return (0);
}

int ft_count_words(char *str, char c)
{
    int nbword;

    nbword = 0;
    while (*str)
    {
        if (*str == c)
            str++;
        while (*str != c && *str)
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
    tab[nbword] = 0;
    i = -1;
    while (++i < nbword)
    {
        j = 0;
        if (*str == c)
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
    return (tab);
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

int ft_deal_key(int key, void *param)
{
    t_glob *glob;

    glob = (t_glob *)param;
    if (key == ESC)
        return (ft_exit(glob), 1);
    if (key == TAB)
            return (1);
    if (key == M)
    {
        if (glob->minimap == 0)
            glob->minimap = 1;
        else if (glob->minimap == 1)
            glob->minimap = 0;
    }
    else if (key == Z || key == Q || key == S || key == D || key == L_ARROW || key == R_ARROW)
            ft_move(glob, key);
    if (glob->minimap == 1)
    {
        ft_raycasting(glob);
        ft_minimap(glob);
    }
    else
        ft_raycasting(glob);
    return (0);
}

void    ft_init_img(t_glob *glob)
{
    glob->n_img->h = RES;
    glob->n_img->w = RES;
    glob->n_img->bpp = 8;
    glob->n_img->sl = 8 * RES;
    glob->n_img->e = 0;
    glob->s_img->h = RES;
    glob->s_img->w = RES;
    glob->s_img->bpp = 8;
    glob->s_img->sl = 8 * RES;
    glob->s_img->e = 0;
    glob->w_img->h = RES;
    glob->w_img->w = RES;
    glob->w_img->bpp = 8;
    glob->w_img->sl = 8 * RES;
    glob->w_img->e = 0;
    glob->e_img->h = RES;
    glob->e_img->w = RES;
    glob->e_img->bpp = 8;
    glob->e_img->sl = 8 * RES;
    glob->e_img->e = 0;
}

int   ft_screen(t_glob *glob)
{
    ft_init_img(glob);
    glob->n_img->ptr = mlx_xpm_file_to_image(glob->mlx_ptr, glob->n_img->path_texture, &glob->n_img->w, &glob->n_img->h);
    if (glob->n_img->ptr == NULL)
        return (1);
    glob->n_img->data = (int *)mlx_get_data_addr(glob->n_img->ptr, &glob->n_img->bpp, &glob->n_img->sl, &glob->n_img->e);
    glob->s_img->ptr = mlx_xpm_file_to_image(glob->mlx_ptr, glob->s_img->path_texture, &glob->s_img->w, &glob->s_img->h);
    if (glob->s_img->ptr == NULL)
        return (1);
    glob->s_img->data = (int *)mlx_get_data_addr(glob->s_img->ptr, &glob->s_img->bpp, &glob->s_img->sl, &glob->s_img->e);
    glob->e_img->ptr = mlx_xpm_file_to_image(glob->mlx_ptr, glob->e_img->path_texture, &glob->e_img->w, &glob->e_img->h);
    if (glob->e_img->ptr == NULL)
        return (1);
    glob->e_img->data = (int *)mlx_get_data_addr(glob->e_img->ptr, &glob->e_img->bpp, &glob->e_img->sl, &glob->e_img->e);
    glob->w_img->ptr = mlx_xpm_file_to_image(glob->mlx_ptr, glob->w_img->path_texture, &glob->w_img->w, &glob->w_img->h);
    if (glob->w_img->ptr == NULL)
        return (1);
    glob->w_img->data = (int *)mlx_get_data_addr(glob->w_img->ptr, &glob->w_img->bpp, &glob->w_img->sl, &glob->w_img->e);
    return (0);
}

int ft_mouse(int button, int x, int y, void *param)
{
    t_glob *glob;

    (void)y;
    glob = (t_glob *)param;
    if (button == 1)
    {
        glob->pa += (x - SCREEN_W / 2) * (DR * FOV / SCREEN_W);
        if (glob->pa < 0)
            glob->pa += 2 * PI;
        else if (glob->pa > 2 * PI)
            glob->pa -= 2 * PI;
        ft_raycasting(glob);
    }
    if (glob->minimap == 1)
    {
        ft_raycasting(glob);
        ft_minimap(glob);
    }
    return (0);
}

int main(int argc, char **argv)
{
    t_glob   glob[1];

    glob->minimap = 0;
    if (argc != 2)
        return (1);
    ft_parsing(argv[1], glob);
    glob->ceiling = -1;
    glob->floor = -1;
    if (ft_get_textures(glob, -1) != 0)
        return (1);
    glob->free_map = glob->map;
    glob->map += glob->map_begin;
    ft_verif_map(glob->map, glob);
    glob->mlx_ptr = mlx_init();
	if (!glob->mlx_ptr)
		return (ft_free(glob), 1);
	glob->win_ptr = mlx_new_window(glob->mlx_ptr, SCREEN_W, SCREEN_H, "cub3d");
    glob->image = mlx_new_image(glob->mlx_ptr, SCREEN_W, SCREEN_H);
    glob->data = (int *)mlx_get_data_addr(glob->image, &glob->s_img->bpp, &glob->s_img->sl, &glob->s_img->e);
    if (ft_screen(glob) == 0)
    {
        ft_raycasting(glob);
        mlx_hook(glob->win_ptr, 2, (1L<<0), &ft_deal_key, glob);
        mlx_hook(glob->win_ptr, 4, (1L<<2), &ft_mouse, glob);
        mlx_hook(glob->win_ptr, 17, 0, &ft_exit, glob);
        mlx_loop(glob->mlx_ptr);
    }
    mlx_destroy_window(glob->mlx_ptr, glob->win_ptr);
    mlx_destroy_image(glob->mlx_ptr, glob->image);
    ft_free(glob);
    mlx_destroy_display(glob->mlx_ptr);
    free(glob->mlx_ptr);
    return (0);
}