/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_textures_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <achatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 18:02:25 by achatela          #+#    #+#             */
/*   Updated: 2022/09/08 18:12:42 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_map(t_glob *glob)
{
	int	i;

	i = 0;
	while (glob->map[i] != 0)
	{
		free(glob->map[i]);
		i++;
	}
	free(glob->map);
	if (glob->n_img->path_texture != NULL)
		free(glob->n_img->path_texture);
	if (glob->s_img->path_texture != NULL)
		free(glob->s_img->path_texture);
	if (glob->e_img->path_texture != NULL)
		free(glob->e_img->path_texture);
	if (glob->w_img->path_texture != NULL)
		free(glob->w_img->path_texture);
}

int	check_direction(char first, char second)
{
	if (first == 'C' && second == ' ')
		return (2);
	else if (first == 'F' && second == ' ')
		return (2);
	else if (first == 'N' && second == 'O')
		return (2);
	else if (first == 'S' && second == 'O')
		return (2);
	else if (first == 'W' && second == 'E')
		return (2);
	else if (first == 'E' && second == 'A')
		return (2);
	else if (first == '\0')
		return (2);
	else
		return (1);
}

int	ft_check_integer(char **number)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (number[i][++j] != '\0')
		{
			if (number[i][j] < 48 || number[i][j] > 57)
				return (1);
		}
	}
	return (0);
}

int	ft_rgb_error2(char **number)
{
	if (((number[0][0] != '-' && ft_strlen_custom(number[0]) > 3)
		|| (number[1][0] != '-' && ft_strlen_custom(number[1]) > 3)
		|| (number[2][0] != '-' && ft_strlen_custom(number[2]) > 3))
		|| (ft_strlen_custom(number[0]) > 4)
		|| ft_strlen_custom(number[1]) > 4
		|| ft_strlen_custom(number[2]) > 4)
	{
		printf("Error\nRGB Value contain more than 3 numbers\n");
		return (1);
	}
	if (ft_atoi(number[0]) < 0
		|| ft_atoi(number[1]) < 0 || ft_atoi(number[2]) < 0)
	{
		printf("Error\nRGB Value is negative\n");
		return (1);
	}
	if (ft_atoi(number[0]) > 255
		|| ft_atoi(number[1]) > 255 || ft_atoi(number[2]) > 255)
	{
		printf("Error\nRGB Value is higher than 255\n");
		return (1);
	}
	return (0);
}

int	ft_rgb_error(char **number)
{
	if (number[0] == 0 || number[1] == 0 || number[2] == 0)
	{
		printf("Error\nRGB Format error (Too few arguments)\n");
		return (1);
	}
	if (number[3] != 0)
	{
		printf("Error\nRGB Format error (Too many arguments)\n");
		return (1);
	}
	if (ft_check_integer(number) == 1)
	{
		printf("Error\nRGB value is not an integer !\n");
		return (1);
	}
	if (ft_rgb_error2(number) == 1)
		return (1);
	return (0);
}
