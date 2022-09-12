/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <achatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 02:16:59 by hcarpent          #+#    #+#             */
/*   Updated: 2022/09/12 15:38:25 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_count_words(char *str, char c)
{
	int	nbword;

	nbword = 0;
	while (*str)
	{
		if (*str == c)
			str++;
		while (*str != c && *str)
			str++;
		nbword++;
	}
	return (nbword);
}

char	**ft_split_modif(char *str, char c, int i, int k)
{
	char	**tab;
	int		j;

	tab = malloc(sizeof(char *) * (k + 1));
	if (!tab)
		return (NULL);
	tab[k] = 0;
	while (++i < k)
	{
		j = 0;
		if (*str == c)
			str++;
		while (*str != c && *str && ++j != 0)
			str++;
		tab[i] = malloc(sizeof(char) * (j + 1));
		if (!tab[i])
			return (NULL);
		tab[i][j] = '\0';
		str -= j;
		j = 0;
		while (*str != c && *str)
			tab[i][j++] = *str++;
	}
	return (tab);
}

int	ft_parsing(char *mapfile, t_glob *glob, int size)
{
	char	*mapstr;
	char	buf;
	int		fd;

	glob->map = NULL;
	fd = open(mapfile, O_RDONLY);
	if (fd < 0 || fd > 1024 || read(fd, &buf, 0) < 0)
		return (printf("Error\nCouldn't open file\n"), 1);
	while (read(fd, &buf, 1))
		size++;
	close(fd);
	mapstr = malloc(sizeof(char) * (size + 1));
	if (!mapstr)
		exit(1);
	mapstr[size] = '\0';
	fd = open(mapfile, O_RDONLY);
	read(fd, mapstr, size);
	close(fd);
	glob->map = ft_split_modif(mapstr, '\n', -1, ft_count_words(mapstr, '\n'));
	free(mapstr);
	return (0);
}

void	main2(t_glob *glob)
{
	glob->win_ptr = mlx_new_window(glob->mlx_ptr, SCREEN_W, SCREEN_H, "cub3d");
	glob->image = mlx_new_image(glob->mlx_ptr, SCREEN_W, SCREEN_H);
	glob->data = (int *)mlx_get_data_addr(glob->image,
			&glob->s_img->bpp, &glob->s_img->sl, &glob->s_img->e);
	if (ft_screen(glob) == 0)
	{
		ft_raycasting(glob);
		mlx_hook(glob->win_ptr, 2, (1L << 0), &ft_deal_key, glob);
		mlx_hook(glob->win_ptr, 4, (1L << 2), &ft_mouse, glob);
		mlx_hook(glob->win_ptr, 17, 0, &ft_exit, glob);
		mlx_loop(glob->mlx_ptr);
	}
	mlx_destroy_window(glob->mlx_ptr, glob->win_ptr);
	mlx_destroy_image(glob->mlx_ptr, glob->image);
	ft_free(glob);
	mlx_destroy_display(glob->mlx_ptr);
	free(glob->mlx_ptr);
}

int	main(int argc, char **argv)
{
	t_glob	glob[1];

	glob->minimap = 0;
	if (argc != 2)
		return (printf("Error\nFormat ./cub3D path_to_map\n"), 1);
	argc = ft_strlen(argv[1]);
	if (argv[1][argc - 4] != '.' || argv[1][argc - 3] != 'c'
		|| argv[1][argc - 2] != 'u' || argv[1][argc - 1] != 'b')
		return (printf("Error\nFile extension not .cub\n"), 1);
	if (ft_parsing(argv[1], glob, 0) == 1)
		return (1);
	glob->ceiling = -1;
	glob->floor = -1;
	if (ft_get_textures(glob, -1) != 0)
		return (ft_free(glob), 1);
	glob->free_map = glob->map;
	glob->map += glob->map_begin;
	ft_verif_map(glob);
	glob->mlx_ptr = mlx_init();
	if (!glob->mlx_ptr)
		return (ft_free(glob), 1);
	main2(glob);
	return (0);
}
