SRC	=		main.c ft_get_textures.c ft_atoi.c ft_modelisation.c ft_minimap.c ft_move.c ft_free.c ft_verif_map.c ft_assign_texture.c ft_get_textures_utils.c ft_get_textures_utils2.c ft_minimap_lines.c ft_utils.c ft_utils2.c ft_get_textures_utils3.c

OBJ	=		$(SRC:.c=.o)

CFLAGS =	-Wall -Werror -Wextra

NAME =		cub3D

CC =		gcc
RM =		rm -f

all: $(NAME)

%.o: %.c  cub3d.h
			$(CC) $(CFLAGS) -I/usr/include -Imlx -c $< -o $@

$(NAME): $(OBJ)
			$(CC) $(CFLAGS) $(OBJ)  -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz -o $(NAME)

clean:
			$(RM) $(OBJ)

fclean: clean
			$(RM) $(NAME)

re: 		fclean all

.PHONY:		all clean fclean re
