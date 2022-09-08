/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap_lines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <achatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 19:14:33 by achatela          #+#    #+#             */
/*   Updated: 2022/09/08 19:21:04 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	first_line(t_glob *glob, int test)
{
	int	i;
	int	j;
	int	scale;

	scale = 0;
	j = -2;
	i = -1;
	while (++i < 5)
	{
		if (((int)(glob->py / SQR_SIZE) - 2) < 0
			|| (int)((glob->px / SQR_SIZE) + j) < 0
			|| (int)((glob->px / SQR_SIZE) + j)
			> ft_strlen(glob->map[(int)((glob->py / SQR_SIZE) - 2)]))
			ft_draw_square(glob, scale, 0, 0);
		else if (glob->map[(int)(glob->py / SQR_SIZE) - 2]
					[(int)(glob->px / SQR_SIZE) + j] == '1')
			ft_draw_square(glob, scale, 0, 16000000);
		else if (glob->map[(int)(glob->py / SQR_SIZE) - 2]
					[(int)(glob->px / SQR_SIZE) + j] == '0')
			ft_draw_square(glob, scale, 0, 1669722);
		else
			ft_draw_square(glob, scale, 0, 0);
		j++;
		scale += test;
	}
}

void	second_line(t_glob *glob, int test)
{
	int	i;
	int	j;
	int	scale;
	int	scale_fix;

	scale_fix = test;
	scale = 0;
	j = -2;
	i = -1;
	while (++i < 5)
	{
		if (((int)(glob->py / SQR_SIZE) - 1) < 0
			|| (int)((glob->px / SQR_SIZE) + j) < 0)
			ft_draw_square(glob, scale, scale_fix, 0);
		else if (glob->map[(int)(glob->py / SQR_SIZE) - 1]
					[(int)(glob->px / SQR_SIZE) + j] == '1')
			ft_draw_square(glob, scale, scale_fix, 16000000);
		else if (glob->map[(int)(glob->py / SQR_SIZE) - 1]
					[(int)(glob->px / SQR_SIZE) + j] == '0')
			ft_draw_square(glob, scale, scale_fix, 1669722);
		else
			ft_draw_square(glob, scale, scale_fix, 0);
		j++;
		scale += test;
	}
}

void	third_line(t_glob *glob, int test)
{
	int	i;
	int	j;
	int	scale;

	scale = 0;
	j = -2;
	i = -1;
	while (++i < 5)
	{
		if (((int)(glob->py / SQR_SIZE)) < 0
				|| (int)((glob->px / SQR_SIZE) + j) < 0
				|| (int)((glob->px / SQR_SIZE) + j)
				> ft_strlen(glob->map[(int)((glob->py / SQR_SIZE))]))
			ft_draw_square(glob, scale, test * 2, 0);
		else if (glob->map[(int)(glob->py / SQR_SIZE)]
					[(int)(glob->px / SQR_SIZE) + j] == '1')
			ft_draw_square(glob, scale, test * 2, 16000000);
		else if (glob->map[(int)(glob->py / SQR_SIZE)]
					[(int)(glob->px / SQR_SIZE) + j] == '0')
			ft_draw_square(glob, scale, test * 2, 1669722);
		else
			ft_draw_square(glob, scale, test * 2, 0);
		j++;
		scale += test;
	}
}

void	forth_line(t_glob *glob, int test, int k)
{
	int	i;
	int	j;
	int	scale;
	int	scale_fix;

	scale_fix = test * 3;
	scale = 0;
	j = -2;
	i = -1;
	while (++i < 5)
	{
		if (((int)(glob->py / SQR_SIZE) + 1) < k - k
			|| (int)((glob->px / SQR_SIZE) + j) < 0)
			ft_draw_square(glob, scale, scale_fix, 0);
		else if (glob->map[(int)(glob->py / SQR_SIZE) + 1]
					[(int)(glob->px / SQR_SIZE) + j] == '1')
			ft_draw_square(glob, scale, scale_fix, 16000000);
		else if (glob->map[(int)(glob->py / SQR_SIZE) + 1]
					[(int)(glob->px / SQR_SIZE) + j] == '0')
			ft_draw_square(glob, scale, scale_fix, 1669722);
		else
			ft_draw_square(glob, scale, scale_fix, 0);
		j++;
		scale += test;
	}
}

void	fifth_line(t_glob *glob, int test, int k)
{
	int	i;
	int	j;
	int	scale;
	int	scale_fix;

	scale_fix = test * 4;
	scale = 0;
	j = -2;
	i = -1;
	while (++i < 5)
	{
		if (((int)(glob->py / SQR_SIZE) + 2) > k - 1
			|| (int)((glob->px / SQR_SIZE) + j) < 0)
			ft_draw_square(glob, scale, scale_fix, 0);
		else if (glob->map[(int)(glob->py / SQR_SIZE) + 2]
					[(int)(glob->px / SQR_SIZE) + j] == '1')
			ft_draw_square(glob, scale, scale_fix, 16000000);
		else if (glob->map[(int)(glob->py / SQR_SIZE) + 2]
					[(int)(glob->px / SQR_SIZE) + j] == '0')
			ft_draw_square(glob, scale, scale_fix, 1669722);
		else
			ft_draw_square(glob, scale, scale_fix, 0);
		j++;
		scale += test;
	}
}
