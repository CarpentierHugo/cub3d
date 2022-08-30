/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modelisation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <achatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:52:13 by achatela          #+#    #+#             */
/*   Updated: 2022/08/30 16:29:06 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    ft_modelisation(t_glob *glob, float length, int i, float rx, float ry, float ra, int **data)
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
    float   sinry;
    float   cosrx;

    ca = glob->pa - ra;
    if (ca < 0)
        ca += 2 * PI;
    if (ca > 2 * PI)
        ca -= 2 * PI;
    length *= cos(ca);
    lineh = SQR_SIZE * SCREEN_H / length;
    ty_step = RES / lineh;
    ty_off = 0;
    if (lineh > SCREEN_H)
    {
        ty_off = (lineh - SCREEN_H) / 2;
        lineh = SCREEN_H;
    }
    lineo = SCREEN_H / 2 - (lineh / 2);
    ty = ty_off * ty_step;
    y = -1;
    sinry = ry - sin(ra);
    cosrx = rx - cos(ra);
    while (++y < lineh)
    {
            tx = (int)(((int)rx + (int)ry) / (SQR_SIZE / RES)) % RES;
            if (glob->map[(int)((ry - 1) / SQR_SIZE)][(int)(rx / SQR_SIZE)] != '1' && (int)((ry - 1) / SQR_SIZE) == (int)((sinry) / SQR_SIZE))
                c = glob->n_img->data[(int)tx + (int)ty * RES];
            else if (glob->map[(int)((ry + 1) / SQR_SIZE)][(int)(rx / SQR_SIZE)] != '1' && (int)((ry + 1) / SQR_SIZE) == (int)((sinry) / SQR_SIZE))
                c = glob->s_img->data[(int)tx + (int)ty * RES];
            else if (glob->map[(int)(ry / SQR_SIZE)][(int)((rx + 1) / SQR_SIZE)] != '1' && (int)((rx + 1) / SQR_SIZE) == (int)((cosrx) / SQR_SIZE))
                c = glob->e_img->data[(int)tx + (int)ty * RES];
            else if (glob->map[(int)(ry / SQR_SIZE)][(int)((rx - 1) / SQR_SIZE)] != '1' && (int)((rx - 1) / SQR_SIZE) == (int)((cosrx) / SQR_SIZE))
                c = glob->w_img->data[(int)tx + (int)ty * RES];
            else
            {
                if ((ra <= PI / 4 && ra >= 0) || (ra >= 7 * PI / 4 && ra <= 2 * PI))
                    c = glob->w_img->data[(int)tx + (int)ty * RES];
                else if (ra >= 5 * PI / 4 && ra <= 7 * PI / 4)
                    c = glob->s_img->data[(int)tx + (int)ty * RES];
                else if (ra >= 3 * PI / 4 && ra <= 5 * PI / 4)
                    c = glob->e_img->data[(int)tx + (int)ty * RES];
                else if (ra >= PI / 4 && ra <= 3 * PI / 4)
                    c = glob->n_img->data[(int)tx + (int)ty * RES];
            }
            data[0][(int)(i + (y + lineo) * SCREEN_W)] = c;
            ty += ty_step;
    }
    y = -1;
    while (++y < lineo)
        data[0][(int)(i + y * SCREEN_W)] = glob->ceiling;
    y = lineo + lineh - 1;
    while (++y < SCREEN_H)
        data[0][(int)(i + y * SCREEN_W)] = glob->floor;
}
