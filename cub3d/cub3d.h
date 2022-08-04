/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <achatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 21:41:45 by hcarpent          #+#    #+#             */
/*   Updated: 2022/08/04 18:19:01 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifdef linux
#  define Z        122
#  define S        115
#  define Q        113
#  define D        100
#  define L_ARROW  65361
#  define R_ARROW  65363
#  define ESC      65307
# else
#  define Z         13
#  define S         1
#  define Q         0
#  define D         2
#  define L_ARROW   123
#  define R_ARROW   124
#  define ESC       53
# endif

#define PI 3.1415926535
#define DR PI / 180
#define SQR_SIZE 64
#define FOV 100
#define MOV_SPD 10
#define ROT_SPD 0.2
#define SCREEN_H 320
#define SCREEN_W 8 * FOV

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mlx/mlx.h"

typedef struct  s_img
{
    char    *path_texture;
    void    *ptr;
    int     *data;
    int     h;
    int     w;
    int     bpp;
    int     sl;
    int     e;
}   t_img;

typedef struct  s_glob
{
    char    **map;
    void	*mlx_ptr;
	void	*win_ptr;
    t_img   n_img[1];
    t_img   s_img[1];
    t_img   e_img[1];
    t_img   w_img[1];
    int     floor;
    int     ceiling;
    float   px;
    float   py;
    float   pa;
}   t_glob;

void    ft_get_textures(t_glob *glob, int i, int j);

#endif
