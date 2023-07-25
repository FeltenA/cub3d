SRCS	=	src/cub3d.c\
			src/parse/parse.c\
			src/parse/parse_utils.c\
			src/parse/parse_map.c\
			src/parse/parse_check.c\
			src/display/raycasting.c\
			src/display/texture.c\
			src/display/display.c\
			src/display/draw.c\
			src/display/minimap.c\
			src/free.c\
			src/init.c

OBJS	=	${SRCS:.c=.o}

NAME	=	cub3d

LIBFT	=	./libft/libft.a

INC		=	-I ./include

CC		=	cc

RM		=	rm -f

CFLAGS	=	-Wall -Wextra -Werror

MLXFLAGS=	-I/usr/include -Iminilibx-linux -O3

%.o:		%.c
		${CC} ${CFLAGS} ${MLXFLAGS} -c $< -o $@ ${INC}

all:		${NAME}

${NAME}:	mlxlb ${LIBFT} ${OBJS}
		${CC} ${OBJS} -o ${NAME} ${INC} ${LIBFT} -Lminilibx-linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

${LIBFT}:
		@make added -C libft
		cp ./libft/include/libft.h ./include

mlxlb:
		$(MAKE) -C minilibx-linux

clean:
		${RM} ${OBJS}
		@make clean -C libft

fclean:		clean
		${RM} ${NAME}
		@make fclean -C libft
		${RM} ./include/libft.a
		cd minilibx-linux
		@make clean -C minilibx-linux

re:		fclean
		make all

.PHONY:		all clean fclean re bonus mlxlb
