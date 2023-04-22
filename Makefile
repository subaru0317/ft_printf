NAME	=	libftprintf.a
CC		=	cc
# CFLAGS	=	-Wall -Wextra -Werror
SRCDIR	=	./
SRCNAME	=	ft_printf.c libft_extend_utils.c math_utils.c
SRCS	=	${addprefix ${SRCDIR}, ${SRCNAME}}
OBJS	=	${SRCS:.c=.o}
INCLUDES = ./inlcudes/libft.a

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			${MAKE} -C ./libft
			cp libft/libft.a ${NAME}
			ar rcs ${NAME} ${OBJS}

all:		${NAME}

clean:		
			${MAKE} -C ./libft clean
			${RM} ${OBJS}

fclean:		clean
			${MAKE} -C ./libft fclean
			${RM} ${NAME}

re:			fclean all

.PHONY:	all clean fclean re