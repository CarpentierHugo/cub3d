/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_textures_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <achatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 18:04:43 by achatela          #+#    #+#             */
/*   Updated: 2022/09/08 18:13:09 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_get_ceiling(t_glob *glob, char *texture)
{
	char	**number;

	if (glob->ceiling != -1)
		return (1);
	number = NULL;
	number = ft_split_modif(texture, ',', -1, ft_count_words(texture, ','));
	if (number == NULL)
		return (1);
	if (ft_rgb_error(number) == 1)
	{
		ft_free_number(number, 0, glob, 1);
		exit(1);
	}
	glob->ceiling = 0;
	glob->ceiling += ft_atoi(number[0]) * 65536;
	glob->ceiling += ft_atoi(number[1]) * 256;
	glob->ceiling += ft_atoi(number[2]);
	ft_free_number(number, 0, glob, 0);
	return (0);
}

int	ft_get_floor(t_glob *glob, char *texture)
{
	char	**number;

	if (glob->floor != -1)
		return (1);
	number = NULL;
	number = ft_split_modif(texture, ',', -1, ft_count_words(texture, ','));
	if (number == NULL)
		return (1);
	if (ft_rgb_error(number) == 1)
	{
		ft_free_number(number, 0, glob, 1);
		exit(1);
	}
	glob->floor = 0;
	glob->floor += ft_atoi(number[0]) * 65536;
	glob->floor += ft_atoi(number[1]) * 256;
	glob->floor += ft_atoi(number[2]);
	ft_free_number(number, 0, glob, 0);
	return (0);
}

int	ft_path_texture(t_glob *glob, char direction, int j, char *texture)
{
	int	len;
	int	ret;

	ret = 0;
	len = j;
	if (direction == 'C')
		ret = ft_get_ceiling(glob, texture);
	else if (direction == 'F')
		ret = ft_get_floor(glob, texture);
	else if (direction == 'N')
		ret = ft_north_texture(glob, texture, len - j + 4);
	else if (direction == 'S')
		ret = ft_south_texture(glob, texture, len - j + 4);
	else if (direction == 'W')
		ret = ft_west_texture(glob, texture, len - j + 4);
	else if (direction == 'E')
		ret = ft_east_texture(glob, texture, len - j + 4);
	else
		ret = 1;
	return (ret);
}

int	ft_map_beginning(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '1' || str[i] == '0' || str[i] == 'N'
			|| str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
			return (1);
		else
			i++;
	}
	return (0);
}

int	ft_str_is_beginning(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '1' || str[i] == '0')
		return (1);
	return (0);
}
