SRCS	=	src/ft_isalpha.c\
			src/ft_isdigit.c\
			src/ft_isalnum.c\
			src/ft_isascii.c\
			src/ft_isprint.c\
			src/ft_strlen.c\
			src/ft_memset.c\
			src/ft_bzero.c\
			src/ft_memcpy.c\
			src/ft_memmove.c\
			src/ft_strlcpy.c\
			src/ft_strlcat.c\
			src/ft_toupper.c\
			src/ft_tolower.c\
			src/ft_strchr.c\
			src/ft_strrchr.c\
			src/ft_strncmp.c\
			src/ft_memchr.c\
			src/ft_memcmp.c\
			src/ft_strnstr.c\
			src/ft_atoi.c\
			src/ft_calloc.c\
			src/ft_strdup.c\
			src/ft_substr.c\
			src/ft_strjoin.c\
			src/ft_strtrim.c\
			src/ft_split.c\
			src/ft_itoa.c\
			src/ft_strmapi.c\
			src/ft_striteri.c\
			src/ft_putchar_fd.c\
			src/ft_putstr_fd.c\
			src/ft_putendl_fd.c\
			src/ft_putnbr_fd.c

SRCSB	= 	src_bonus/ft_lstnew_bonus.c\
			src_bonus/ft_lstadd_front_bonus.c\
			src_bonus/ft_lstsize_bonus.c\
			src_bonus/ft_lstlast_bonus.c\
			src_bonus/ft_lstadd_back_bonus.c\
			src_bonus/ft_lstdelone_bonus.c\
			src_bonus/ft_lstclear_bonus.c\
			src_bonus/ft_lstiter_bonus.c\
			src_bonus/ft_lstmap_bonus.c

SRCSADD	=	src_added/get_next_line_bonus.c\
			src_added/get_next_line_utils_bonus.c\
			src_added/ft_realloc.c\
			src_added/ft_strcmp.c\
			src_added/ft_split_funct.c\
			src_added/ft_isspace.c\
			src_added/ft_array_free.c\
			src_added/ft_array_len.c\
			src_added/ft_isinlist.c\
			src_added/ft_free_ptr.c\
			src_added/ft_array_exec.c

OBJS	= ${SRCS:.c=.o}

OBJSB	= ${SRCSB:.c=.o}

OBJSADD	= ${SRCSADD:.c=.o}

HEAD	= include

NAME	= libft.a

CC		= cc

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror

%.o:		%.c
		${CC} ${CFLAGS} -c $< -o $@ -I${HEAD}

${NAME}:	${OBJS}
		ar rc ${NAME} ${OBJS}
		ranlib ${NAME}

all:		${NAME}

clean:
		${RM} ${OBJS} ${OBJSB} ${OBJSADD}

fclean:		clean
		${RM} ${NAME}

re:		fclean all

bonus:		${NAME} ${OBJSB}
		ar r ${NAME} ${OBJSB}
		ranlib ${NAME}

added:		bonus ${OBJSADD}
		ar r ${NAME} ${OBJSADD}
		ranlib ${NAME}

.PHONY:		all clean fclean re bonus added
