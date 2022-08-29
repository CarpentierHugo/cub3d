/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modelisation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <achatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:52:13 by achatela          #+#    #+#             */
/*   Updated: 2022/08/29 17:51:52 by achatela         ###   ########.fr       */
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
    int     j;
    int     irx = (int)rx;
    int     iry = (int)ry;

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
            tx = (int)((irx + iry) / (SQR_SIZE / RES)) % RES;  //remplacer RES
            j = 0;
            if (glob->map[(int)((iry - 1) / SQR_SIZE)][(int)(irx / SQR_SIZE)] != '1')
            {
                c = glob->n_img->data[(int)tx + (int)ty * RES];
                j++;
            }
            if (glob->map[(int)((iry + 1) / SQR_SIZE)][(int)(irx / SQR_SIZE)] != '1')
            {
                c = glob->s_img->data[(int)tx + (int)ty * RES];
                j++;
            }
            if (glob->map[(int)(iry / SQR_SIZE)][(int)((irx + 1) / SQR_SIZE)] != '1')
            {
                c = glob->e_img->data[(int)tx + (int)ty * RES];
                j++;
            }
            if (glob->map[(int)(iry / SQR_SIZE)][(int)((irx - 1) / SQR_SIZE)] != '1')
            {
                c = glob->w_img->data[(int)tx + (int)ty * RES];
                j++;
            }
            if (!j)
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
            else if (j == 2)
            {
                if (&glob->map[(int)((ry - 1) / SQR_SIZE)][(int)(rx / SQR_SIZE)] == &glob->map[(int)((ry - sin(ra)) / SQR_SIZE)][(int)((rx - cos(ra)) / SQR_SIZE)] && glob->map[(int)((iry - 1) / SQR_SIZE)][(int)(irx / SQR_SIZE)] != '1')
                    c = glob->n_img->data[(int)tx + (int)ty * RES];
                if (&glob->map[(int)((ry + 1) / SQR_SIZE)][(int)(rx / SQR_SIZE)] == &glob->map[(int)((ry - sin(ra)) / SQR_SIZE)][(int)((rx - cos(ra)) / SQR_SIZE)] && glob->map[(int)((iry + 1) / SQR_SIZE)][(int)(irx / SQR_SIZE)] != '1')
                    c = glob->s_img->data[(int)tx + (int)ty * RES];
                if (&glob->map[(int)(ry / SQR_SIZE)][(int)((rx + 1) / SQR_SIZE)] == &glob->map[(int)((ry - sin(ra)) / SQR_SIZE)][(int)((rx - cos(ra)) / SQR_SIZE)] && glob->map[(int)(iry / SQR_SIZE)][(int)((irx + 1) / SQR_SIZE)] != '1')
                    c = glob->e_img->data[(int)tx + (int)ty * RES];
                if (&glob->map[(int)(ry / SQR_SIZE)][(int)((rx - 1) / SQR_SIZE)] == &glob->map[(int)((ry - sin(ra)) / SQR_SIZE)][(int)((rx - cos(ra)) / SQR_SIZE)] && glob->map[(int)(iry / SQR_SIZE)][(int)((irx - 1) / SQR_SIZE)] != '1')
                    c = glob->w_img->data[(int)tx + (int)ty * RES];
            }
            data[0][(int)((i + ((y + lineo) * (SCREEN_W))))] = c;
            ty += ty_step;
    }
    y = -1;
    while (++y < lineo)
        data[0][(int)((i) + (y * (SCREEN_W)))] = glob->ceiling; // remplacer par glob->ceiling
    y = lineo + lineh - 1;
    while (++y < SCREEN_H)
        data[0][(int)((i) + (y * (SCREEN_W)))] = glob->floor;
}