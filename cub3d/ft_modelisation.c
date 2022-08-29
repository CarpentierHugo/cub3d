/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modelisation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <achatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:52:13 by achatela          #+#    #+#             */
/*   Updated: 2022/08/29 15:53:22 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int get_texture_color(t_glob *glob, float tx, float ty)
{
    if ((glob->pa <= PI / 4 && glob->pa >= 0) || (glob->pa >= 7 * PI / 4 && glob->pa <= 2 * PI))
        return (glob->w_img->data[(int)tx + (int)ty * RES]);
    else if (glob->pa >= 5 * PI / 4 && glob->pa <= 7 * PI / 4)
        return (glob->s_img->data[(int)tx + (int)ty * RES]);
    else if (glob->pa >= 3 * PI / 4 && glob->pa <= 5 * PI / 4)
        return (glob->e_img->data[(int)tx + (int)ty * RES]);
    else if (glob->pa >= PI / 4 && glob->pa <= 3 * PI / 4)
        return (glob->n_img->data[(int)tx + (int)ty * RES]);
    return (0x00000000);
}

void    ft_modelisation(t_glob *glob, float length, int i, int rx, int ry, float ra, int **data)
{
    float     lineh;
    int       lineo;
    int     y;
    float   ty;
    float   tx;
    float   ty_step;
    int     c;
    float   ty_off;
    float   ca;
    int     j;

    ca = glob->pa - ra;
    if (ca < 0)
        ca += 2 * PI;
    if (ca > 2 * PI)
        ca -= 2 * PI;
    length *= cos(ca);
    lineh = SQR_SIZE * SCREEN_H / length;
    ty_step = RES / lineh; //remplacer RES
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
            tx = (rx + ry) / (SQR_SIZE / RES) % RES;  //remplacer RES
            c = get_texture_color(glob, tx, ty);
            if ((int)ry % SQR_SIZE == 0)
            {  
                if (glob->map[(int)((ry - 1) / SQR_SIZE)][(int)(rx / SQR_SIZE)] != '1' && (glob->map[(int)(ry / SQR_SIZE)][(int)((rx - 1) / SQR_SIZE)] != '1' || glob->map[(int)(ry / SQR_SIZE)][(int)((rx + 1) / SQR_SIZE)] != '1'))
                {
                    if (&glob->map[(int)((ry - sin(ra)) / SQR_SIZE)][(int)((rx - cos(ra)) / SQR_SIZE)] == &glob->map[(int)((ry - 1) / SQR_SIZE)][(int)(rx / SQR_SIZE)])
                        c = glob->n_img->data[(int)tx + (int)ty * RES];
                }
                else if (glob->map[(int)((ry - 1) / SQR_SIZE)][(int)(rx / SQR_SIZE)] != '1')
                    c = glob->n_img->data[(int)tx + (int)ty * RES];
            }   
            else if ((int)ry % SQR_SIZE == SQR_SIZE - 1)
            {  
                if (glob->map[(int)((ry + 1) / SQR_SIZE)][(int)(rx / SQR_SIZE)] != '1' && (glob->map[(int)(ry / SQR_SIZE)][(int)((rx - 1) / SQR_SIZE)] != '1' || glob->map[(int)(ry / SQR_SIZE)][(int)((rx + 1) / SQR_SIZE)] != '1'))
                {
                    if (&glob->map[(int)((ry - sin(ra)) / SQR_SIZE)][(int)((rx - cos(ra)) / SQR_SIZE)] == &glob->map[(int)((ry + 1) / SQR_SIZE)][(int)(rx / SQR_SIZE)])
                        c = glob->s_img->data[(int)tx + (int)ty * RES];
                }
                else if (glob->map[(int)((ry + 1) / SQR_SIZE)][(int)(rx / SQR_SIZE)] != '1')
                    c = glob->s_img->data[(int)tx + (int)ty * RES];
            }
            if ((int)rx % SQR_SIZE == SQR_SIZE - 1)
            {  
                if (glob->map[(int)(ry / SQR_SIZE)][(int)((rx + 1) / SQR_SIZE)] != '1' && (glob->map[(int)((ry - 1) / SQR_SIZE)][(int)(rx / SQR_SIZE)] != '1' || glob->map[(int)((ry + 1) / SQR_SIZE)][(int)(rx / SQR_SIZE)] != '1'))
                {
                    if (&glob->map[(int)((ry - sin(ra)) / SQR_SIZE)][(int)((rx - cos(ra)) / SQR_SIZE)] == &glob->map[(int)(ry / SQR_SIZE)][(int)((rx + 1) / SQR_SIZE)])
                        c = glob->e_img->data[(int)tx + (int)ty * RES];
                }
                else if (glob->map[(int)(ry / SQR_SIZE)][(int)((rx + 1) / SQR_SIZE)] != '1')
                    c = glob->e_img->data[(int)tx + (int)ty * RES];
            }
            else if ((int)rx % SQR_SIZE == 0)
            {  
                if (glob->map[(int)(ry / SQR_SIZE)][(int)((rx - 1) / SQR_SIZE)] != '1' && (glob->map[(int)((ry - 1) / SQR_SIZE)][(int)(rx / SQR_SIZE)] != '1' || glob->map[(int)((ry + 1) / SQR_SIZE)][(int)(rx / SQR_SIZE)] != '1'))
                {
                    if (&glob->map[(int)((ry - sin(ra)) / SQR_SIZE)][(int)((rx - cos(ra)) / SQR_SIZE)] == &glob->map[(int)(ry / SQR_SIZE)][(int)((rx - 1) / SQR_SIZE)])
                        c = glob->w_img->data[(int)tx + (int)ty * RES];
                }
                else if (glob->map[(int)(ry / SQR_SIZE)][(int)((rx - 1) / SQR_SIZE)] != '1')
                    c = glob->w_img->data[(int)tx + (int)ty * RES];
            }
            data[0][(int)((i + ((y + lineo) * (SCREEN_W))))] = c;
            ty += ty_step;
    }
    j = -1;
    while (++j < lineo)
        data[0][(int)((i) + (j * (SCREEN_W)))] = glob->ceiling; // remplacer par glob->ceiling
    j = lineo + lineh - 1;
    while (++j < SCREEN_H)
        data[0][(int)((i) + (j * (SCREEN_W)))] = glob->floor;
}