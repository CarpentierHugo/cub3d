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

void	ft_z(t_glob *glob, float i)
{
	glob->s = sin(glob->pa);
	glob->c = cos(glob->pa);
	while (i < MOV_SPD + 1)
	{
		if (glob->map[(int)((glob->py + glob->s * i) / SQR)]
			[(int)((glob->px + glob->c * i) / SQR)] != '1'
			&& glob->map[(int)((glob->py + glob->s * i) / SQR)]
			[(int)((glob->px + glob->c * i) / SQR)] != '\0'
			&& glob->map[(int)((glob->py + glob->s * i) / SQR)]
			[(int)((glob->px + glob->c * i) / SQR)] != ' ')
			i += 0.1;
		else
			break ;
	}
	if (i >= MOV_SPD + 1)
	{
		glob->px += (glob->c * MOV_SPD);
		glob->py += (glob->s * MOV_SPD);
	}
}

void	ft_q(t_glob *glob, float i)
{
	glob->s = sin(glob->pa);
	glob->c = cos(glob->pa);
	while (i < MOV_SPD + 1)
	{
		if (glob->map[(int)((glob->py - glob->c * i) / SQR)]
			[(int)((glob->px + glob->s * i) / SQR)] != '1'
			&& glob->map[(int)((glob->py - glob->c * i) / SQR)]
			[(int)((glob->px + glob->s * i) / SQR)] != '\0'
			&& glob->map[(int)((glob->py - glob->c * i) / SQR)]
			[(int)((glob->px + glob->s * i) / SQR)] != ' ')
			i += 0.1;
		else
			break;
	}
	if (i >= MOV_SPD + 1)
	{
		if (glob->map[(int)((glob->py + glob->s * MOV_SPD) / SQR)]
			[(int)((glob->px + glob->c * MOV_SPD) / SQR)] != '1'
			&& glob->map[(int)((glob->py + glob->s * MOV_SPD) / SQR)]
			[(int)((glob->px + glob->c * MOV_SPD) / SQR)] != '\0'
			&& glob->map[(int)((glob->py + glob->s * MOV_SPD) / SQR)]
			[(int)((glob->px + glob->c * MOV_SPD) / SQR)] != ' ')
		{
			glob->px += (glob->s * MOV_SPD);
			glob->py -= (glob->c * MOV_SPD);
		}
	}
}

void	ft_s(t_glob *glob, float i)
{
	glob->s = sin(glob->pa);
	glob->c = cos(glob->pa);
	while (i < MOV_SPD + 1)
	{
		if (glob->map[(int)((glob->py - glob->s * i) / SQR)]
			[(int)((glob->px - glob->c * i) / SQR)] != '1'
			&& glob->map[(int)((glob->py - glob->s * i) / SQR)]
			[(int)((glob->px - glob->c * i) / SQR)] != '\0'
			&& glob->map[(int)((glob->py - glob->s * i) / SQR)]
			[(int)((glob->px - glob->c * i) / SQR)] != ' ')
			i += 0.1;
		else
			break ;
	}
	if (i >= MOV_SPD + 1)
	{
		glob->px -= (glob->c * MOV_SPD);
		glob->py -= (glob->s * MOV_SPD);
	}
}

void	ft_d(t_glob *glob, float i)
{
	glob->s = sin(glob->pa);
	glob->c = cos(glob->pa);
	while (i < MOV_SPD + 1)
	{
		if (glob->map[(int)((glob->py + glob->c * i) / SQR)]
			[(int)((glob->px - glob->s * i) / SQR)] != '1'
			&& glob->map[(int)((glob->py + glob->c * i) / SQR)]
			[(int)((glob->px - glob->s * i) / SQR)] != '\0'
			&& glob->map[(int)((glob->py + glob->c * i) / SQR)]
			[(int)((glob->px - glob->s * i) / SQR)] != ' ')
			i += 0.1;
		else
			break;
	}
	if (i >= MOV_SPD + 1)
	{
		if (glob->map[(int)((glob->py + glob->s * MOV_SPD) / SQR)]
			[(int)((glob->px + glob->c * MOV_SPD) / SQR)] != '1'
			&& glob->map[(int)((glob->py + glob->s * MOV_SPD) / SQR)]
			[(int)((glob->px + glob->c * MOV_SPD) / SQR)] != '\0'
			&& glob->map[(int)((glob->py + glob->s * MOV_SPD) / SQR)]
			[(int)((glob->px + glob->c * MOV_SPD) / SQR)] != ' ')
		{
			glob->px -= (glob->s * MOV_SPD);
			glob->py += (glob->c * MOV_SPD);
		}
	}
}

void	ft_move(t_glob *glob, int key)
{
	if (key == Z)
		ft_z(glob, 1);
	else if (key == Q)
		ft_q(glob, 1);
	else if (key == S)
		ft_s(glob, 1);
	else if (key == D)
		ft_d(glob, 1);
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
