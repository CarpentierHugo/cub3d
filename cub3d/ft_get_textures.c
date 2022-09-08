/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <achatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:36:59 by achatela          #+#    #+#             */
/*   Updated: 2022/09/08 19:03:21 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strlen_custom(char *str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else
		{
			i++;
			ret++;
		}
	}
	return (ret);
}

void	ft_free_number(char **number, int i, t_glob *glob, int index)
{
	while (number[i] != 0)
	{
		free(number[i]);
		i++;
	}
	if (index == 1)
		ft_free_map(glob);
	free(number);
}

void	ft_set_to_null(t_glob *glob)
{
	glob->n_img->path_texture = NULL;
	glob->s_img->path_texture = NULL;
	glob->w_img->path_texture = NULL;
	glob->e_img->path_texture = NULL;
	glob->n_img->ptr = NULL;
	glob->s_img->ptr = NULL;
	glob->e_img->ptr = NULL;
	glob->w_img->ptr = NULL;
}

int	ft_while_get_textures(t_glob *glob, char direction, int *i, int *c)
{
	int	j;

	j = 0;
	while (glob->map[++(*i)] != 0)
	{
		if (ft_str_is_beginning(glob->map[(*i)]) == 1)
			break ;
		while (glob->map[(*i)][j] && glob->map[(*i)][j] == ' ')
			j++;
		if (glob->map[(*i)][j]
			&& check_direction(glob->map[(*i)][j], glob->map[(*i)][j + 1]) != 0)
			direction = glob->map[(*i)][j];
		if (check_direction(glob->map[(*i)][j], glob->map[(*i)][j + 1]) == 1
			&& (*c) < 6)
			return (printf("Error\nInvalid argument before map\n"), 1);
		if (glob->map[(*i)][j])
			j += 2;
		while (glob->map[(*i)][j] && glob->map[(*i)][j] == ' ')
			j++;
		if (glob->map[(*i)][j])
		{
			if (direction != '\0'
				&& ft_path_texture(glob, direction, j, glob->map[(*i)] + j)
				== 0)
				(*c) += 1;
			else
			{
				if ((*c) < 6)
					return (printf("Error\nToo few argument before map\n")
						, ft_free_map(glob), 1);
				else
					return (printf("Error\nToo many elements before map\n")
						, ft_free_map(glob), 1);
			}
		}
		j = 0;
		direction = '\0';
	}
	return (0);
}

int	ft_get_textures(t_glob *glob, int i)
{
	int		count_texture;
	char	direction;

	direction = '\0';
	count_texture = 0;
	glob->map_begin = -1;
	ft_set_to_null(glob);
	if (ft_while_get_textures(glob, direction, &i, &count_texture) == 1)
		return (1);
	if (count_texture != 6)
		return (printf("Error\nToo few elements before map\n")
			, ft_free_map(glob), 1);
	while (glob->map[i] != 0)
	{
		if (ft_map_beginning(glob->map[i]) == 1)
			break ;
		i++;
	}
	if (glob->map[i] == 0)
	{
		printf("Error\nThere is no map is the file\n");
		return (ft_free_map(glob), 2);
	}
	glob->map_begin = i;
	return (0);
}
