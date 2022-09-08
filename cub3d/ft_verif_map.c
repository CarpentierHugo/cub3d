/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verif_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <achatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 17:35:51 by achatela          #+#    #+#             */
/*   Updated: 2022/09/08 18:38:07 by hcarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_error_map(int error, t_glob *glob)
{
	printf("Error\n");
	if (error == 0)
		printf("Map contains empty lines\n");
	if (error == 1)
		printf("Map contains an invalid character !\n");
	else if (error == 2)
		printf("Too many starting position in glob->map !\n");
	else if (error == 3)
		printf("Map glob->is not surrounded by walls !\n");
	else if (error == 4)
		printf("Map has no walls\n");
	else if (error == 5)
		printf("Map has no floors\n");
	else if (error == 6)
		printf("Map has no starting position\n");
	ft_free(glob);
	exit(1);
}

static void	ft_check_empty_lines(t_glob *glob)
{
	int	i;
	int	j;

	i = -1;
	while (glob->map[++i])
	{
		j = 0;
		while (glob->map[i][j] == ' ')
			j++;
		if (glob->map[i][j] == '\0')
			ft_error_map(0, glob);
	}
}

void	ft_verif_char(int y, int x, t_glob *glob)
{
	if (glob->map[y][x] == '1')
		glob->isone++;
	else if (glob->map[y][x] == '0')
		glob->iszero++;
	else if (glob->map[y][x] == 'N' || glob->map[y][x] == 'S'
		|| glob->map[y][x] == 'E' || glob->map[y][x] == 'W')
	{
		glob->px = x * SQR + SQR / 2;
		glob->py = y * SQR + SQR / 2;
		if (glob->map[y][x] == 'N')
			glob->pa = 3 * PI / 2;
		else if (glob->map[y][x] == 'S')
			glob->pa = PI / 2;
		else if (glob->map[y][x] == 'E')
			glob->pa = 0;
		else if (glob->map[y][x] == 'W')
			glob->pa = PI;
		glob->ispos++;
		glob->map[y][x] = '0';
	}
	else if (glob->map[y][x] != ' ')
		ft_error_map(1, glob);
	if (glob->ispos > 1)
		ft_error_map(2, glob);
}

void	ft_verif_borders(int y, int x, t_glob *glob)
{
	if (glob->map[y][x] != '1' && glob->map[y][x] != ' ')
	{
		if (!y || !x || !glob->map[y + 1] || glob->map[y - 1][x] == ' '
			|| !glob->map[y - 1][x] || glob->map[y][x + 1] == ' '
			|| !glob->map[y][x + 1] || glob->map[y + 1][x] == ' '
			|| !glob->map[y + 1][x] || glob->map[y][x - 1] == ' '
			|| !glob->map[y][x - 1])
			ft_error_map(3, glob);
	}
}

void	ft_verif_map(t_glob *glob)
{
	int	y;
	int	x;

	glob->isone = 0;
	glob->iszero = 0;
	glob->ispos = 0;
	y = -1;
	ft_check_empty_lines(glob);
	while (glob->map[++y])
	{
		x = -1;
		while (glob->map[y][++x])
		{
			ft_verif_char(y, x, glob);
			ft_verif_borders(y, x, glob);
		}
	}
	if (!glob->isone)
		ft_error_map(4, glob);
	if (!glob->iszero)
		ft_error_map(5, glob);
	if (!glob->ispos)
		ft_error_map(6, glob);
}
