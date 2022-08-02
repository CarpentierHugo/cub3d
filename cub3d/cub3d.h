/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarpent <hcarpent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 21:41:45 by hcarpent          #+#    #+#             */
/*   Updated: 2022/08/02 03:24:19 by hcarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#define Z 13
#define Q 0
#define S 1
#define D 2
#define L_ARROW 123
#define R_ARROW 124
#define ESC 53
#define PI 3.1415926535
#define DR PI / 180
#define SQR_SIZE 64
#define FOV 60
#define MOV_SPD 10
#define ROT_SPD 0.2
#define SCREEN_W 320
#define SCREEN_H 8 * FOV

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mlx/mlx.h"

typedef struct  s_img
{
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
    float   px;
    float   py;
    float   pa;
}   t_glob;

char	*ft_strldupfree(const char *s, int len, int f);
char	*ft_strchrdup(const char *s, int c, int d);
char	*ft_strchrr(const char *s, int c);
void	*ft_calloc( size_t elementCount, size_t elementSize);
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
char	*get_next_line(int fd, int buffersize);

#endif
