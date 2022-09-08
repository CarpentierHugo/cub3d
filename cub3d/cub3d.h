/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <achatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 21:41:45 by hcarpent          #+#    #+#             */
/*   Updated: 2022/09/08 19:54:41 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifdef linux
#  define Z        119
#  define S        115
#  define Q        97
#  define D        100
#  define M        109
#  define L_ARROW  65361
#  define R_ARROW  65363
#  define ESC      65307
#  define TAB      65289
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
#define RES 32
#define FOV 60
#define MOV_SPD SQR_SIZE / 10
#define ROT_SPD 0.05
#define SCREEN_H 800
#define SCREEN_W 1200

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
    int     minimap;
    int     infinite;
    char    **map;
    int     *data;
    void    *image;
    char    **free_map;
    void	*mlx_ptr;
	void	*win_ptr;
    t_img   n_img[1];
    t_img   s_img[1];
    t_img   e_img[1];
    t_img   w_img[1];
    int     map_begin;
    long long int     floor;
    long long int     ceiling;
    float   px;
    float   py;
    float   pa;
    int     ispos;
    int     isone;
    int     iszero;
}   t_glob;

int    ft_get_textures(t_glob *glob, int i);
char    **ft_split_modif(char *str, char c, int i);
long long int	ft_atoi(const char *nptr);
void    ft_minimap(t_glob *glob);
void    ft_move(t_glob *glob, int key);
void    ft_free(t_glob *glob);
void    ft_verif_map(t_glob *glob);
void    ft_raycasting(t_glob *glob);
int	ft_north_texture(t_glob *glob, char *texture, int length);
int	ft_south_texture(t_glob *glob, char *texture, int length);
int	ft_west_texture(t_glob *glob, char *texture, int length);
int	ft_east_texture(t_glob *glob, char *texture, int length);
int	ft_rgb_error(char **number);
void	ft_free_map(t_glob *glob);
int	check_direction(char first, char second);
int	ft_check_integer(char **number);
int	ft_rgb_error2(char **number);
int	ft_strlen_custom(char *str);
int	ft_get_ceiling(t_glob *glob, char *texture);
int	ft_get_floor(t_glob *glob, char *texture);
int	ft_path_texture(t_glob *glob, char direction, int j, char *texture);
int	ft_map_beginning(char *str);
int	ft_str_is_beginning(char *str);
void	ft_free_number(char **number, int i, t_glob *glob, int index);
void	first_line(t_glob *glob, int test);
void	second_line(t_glob *glob, int test);
void	third_line(t_glob *glob, int test);
void	forth_line(t_glob *glob, int test, int k);
void	fifth_line(t_glob *glob, int test, int k);
int	ft_strlen(char *str);
void	ft_draw_square(t_glob *glob, int posx, int posy, int color);
int	ft_screen(t_glob *glob);
int	ft_exit(t_glob *glob);
int	ft_mouse(int button, int x, int y, void *param);
void	ft_draw_player(t_glob *glob, int size, int color);
int	ft_deal_key(int key, void *param);

#endif
