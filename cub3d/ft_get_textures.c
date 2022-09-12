/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <achatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:36:59 by achatela          #+#    #+#             */
/*   Updated: 2022/09/12 11:28:05 by achatela         ###   ########.fr       */
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

int	ft_if_while(t_glob *glob, char direction, int *i, int j)
{
	if (direction != '\0'
		&& ft_path_texture(glob, direction, j, glob->map[(*i)] + j)
		== 0)
		glob->count += 1;
	else
	{
		if (glob->count < 6 && glob->n_img->path_texture != NULL
			&& glob->s_img->path_texture != NULL
			&& glob->e_img->path_texture != NULL
			&& glob->w_img->path_texture != NULL
			&& glob->floor != -1 && glob->ceiling != -1)
			return (printf("Error\nToo few argument before map\n")
				, 1);
		else
			return (printf("Error\nToo many elements before map\n")
				, 1);
	}
	return (0);
}

int	ft_while_get_textures(t_glob *glob, char direction, int *i, int j)
{
	while (glob->map[++(*i)] != 0)
	{
		if (ft_str_is_beginning(glob->map[(*i)]) == 1)
			break ;
		while (glob->map[(*i)][j] && glob->map[(*i)][j] == ' ')
			j++;
		if (glob->map[(*i)][j]
			&& check_direction(glob->map[(*i)][j], glob->map[(*i)][j + 1]) != 0)
			direction = glob->map[(*i)][j];
		if (glob->map[(*i)][j] && check_direction(glob->map[(*i)][j],
			glob->map[(*i)][j + 1]) == 1 && glob->count < 6)
			return (printf("Error\nInvalid argument before map\n"), 1);
		if (glob->map[(*i)][j])
			j += 2;
		while (glob->map[(*i)][j] && glob->map[(*i)][j] == ' ')
			j++;
		if (glob->map[(*i)][j] && ft_if_while(glob, direction, i, j) == 1)
			return (1);
		j = 0;
		direction = '\0';
	}
	return (0);
}

int	ft_get_textures(t_glob *glob, int i)
{
	char	direction;

	direction = '\0';
	glob->free_map = glob->map;
	glob->count = 0;
	glob->map_begin = -1;
	ft_set_to_null(glob);
	if (ft_while_get_textures(glob, direction, &i, 0) == 1)
		return (1);
	if (glob->count != 6)
		return (printf("Error\nToo few elements before map\n")
			, 1);
	while (glob->map[i] != 0)
	{
		if (ft_map_beginning(glob->map[i]) == 1)
			break ;
		i++;
	}
	if (glob->map[i] == 0)
	{
		printf("Error\nThere is no map is the file\n");
		return (2);
	}
	glob->map_begin = i;
	return (0);
}
