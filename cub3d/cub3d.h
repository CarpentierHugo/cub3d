/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarpent <hcarpent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 21:41:45 by hcarpent          #+#    #+#             */
/*   Updated: 2022/07/26 19:30:38 by hcarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#define Z 13
#define Q 0
#define S 1
#define D 2
#define ESC 53
#define PI 3.1415926535
#define RES 128
#define FOV 60
#define MOV_SPD 8
#define ROT_SPD 0.2

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mlx/mlx.h"

typedef struct  s_glob
{
    char    **map;
    void	*mlx_ptr;
	void	*win_ptr;
    float   px;
    float   py;
    float   pdx;
    float   pdy;
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
