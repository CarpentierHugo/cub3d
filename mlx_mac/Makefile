SRC	=		main.c ft_get_textures.c

OBJ	=		$(SRC:.c=.o)

CFLAGS =	-Wall -Werror -Wextra

NAME =		cub3d

CC =		gcc
RM =		rm -f

all: $(NAME)

%.o: %.c  cub3d.h
			$(CC) -Imlx -c $< -o $@

$(NAME): $(OBJ)
			$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
			$(RM) $(OBJ)

fclean: clean
			$(RM) $(NAME)

re: 		fclean all

.PHONY:		all clean fclean re
