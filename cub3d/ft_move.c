/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <achatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 17:32:57 by achatela          #+#    #+#             */
/*   Updated: 2022/09/08 17:33:25 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    ft_move(t_glob *glob, int key)
{
    float i;

    i = 1;
    if (key == Z)
    {
        while (i < MOV_SPD + 1)
        {
            if (glob->map[(int)((glob->py + sin(glob->pa) * i) / SQR_SIZE)][(int)((glob->px + cos(glob->pa) * i) / SQR_SIZE)] != '1' && glob->map[(int)((glob->py + sin(glob->pa) * i) / SQR_SIZE)][(int)((glob->px + cos(glob->pa) * i) / SQR_SIZE)] != '\0' && glob->map[(int)((glob->py + sin(glob->pa) * i) / SQR_SIZE)][(int)((glob->px + cos(glob->pa) * i) / SQR_SIZE)] != ' ')
                i += 0.1;
            else
                break ;
        }
        if (i >= MOV_SPD + 1)
        {
            glob->px += (cos(glob->pa) * MOV_SPD);
            glob->py += (sin(glob->pa) * MOV_SPD);
        }
    }
    else if (key == Q)
    {
        while (i < MOV_SPD + 1)
        {
            if (glob->map[(int)((glob->py - cos(glob->pa) * i) / SQR_SIZE)][(int)((glob->px + sin(glob->pa) * i) / SQR_SIZE)] != '1' && glob->map[(int)((glob->py - cos(glob->pa) * i) / SQR_SIZE)][(int)((glob->px + sin(glob->pa) * i) / SQR_SIZE)] != '\0' && glob->map[(int)((glob->py - cos(glob->pa) * i) / SQR_SIZE)][(int)((glob->px + sin(glob->pa) * i) / SQR_SIZE)] != ' ')
                i += 0.1;
            else
                break ;
        }
        if (i >= MOV_SPD + 1)
        {
            glob->px +=(sin(glob->pa) * MOV_SPD);
            glob->py -= (cos(glob->pa) * MOV_SPD);
        }
    }
    else if (key == S)
    {
        while (i < MOV_SPD + 1)
        {
            if (glob->map[(int)((glob->py - sin(glob->pa) * i) / SQR_SIZE)][(int)((glob->px - cos(glob->pa) * i) / SQR_SIZE)] != '1' && glob->map[(int)((glob->py - sin(glob->pa) * i) / SQR_SIZE)][(int)((glob->px - cos(glob->pa) * i) / SQR_SIZE)] != '\0' && glob->map[(int)((glob->py - sin(glob->pa) * i ) / SQR_SIZE)][(int)((glob->px - cos(glob->pa) * i) / SQR_SIZE)] != ' ')
                i += 0.1;
            else
                break ;
        }
        if (i >= MOV_SPD + 1)
        {
            glob->px -= (cos(glob->pa) * MOV_SPD);
            glob->py -= (sin(glob->pa) * MOV_SPD);
        }
    }
    else if (key == D)
    {
        while (i < MOV_SPD + 1)
        {
            if (glob->map[(int)((glob->py + cos(glob->pa) * i) / SQR_SIZE)][(int)((glob->px - sin(glob->pa) * i) / SQR_SIZE)] != '1' && glob->map[(int)((glob->py + cos(glob->pa) * i) / SQR_SIZE)][(int)((glob->px - sin(glob->pa) * i) / SQR_SIZE)] != '\0'
                && glob->map[(int)((glob->py + cos(glob->pa) * i) / SQR_SIZE)][(int)((glob->px - sin(glob->pa) * i) / SQR_SIZE)] != ' ')
                i += 0.1;
            else
                break ;
        }
        if (i >= MOV_SPD + 1)
        {
            glob->px -= (sin(glob->pa) * MOV_SPD);
            glob->py += (cos(glob->pa) * MOV_SPD);
        }
    }
    else if (key == L_ARROW)
    {
        glob->pa -= ROT_SPD;
        if (glob->pa < 0)
            glob->pa += 2 * PI;
    }
    else if (key == R_ARROW)
    {
        glob->pa += ROT_SPD;
        if (glob->pa > 2 * PI)
            glob->pa -= 2 * PI;
    }
}