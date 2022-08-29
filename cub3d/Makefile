SRC	=		main.c ft_get_textures.c ft_atoi.c

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
