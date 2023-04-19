NAME	=	libftprintf.a
CC		=	cc
#CFLAGS	=	-Wall -Wextra -Werror
SRCDIR	=	./
SRCNAME	=	ft_printf.c
SRCS	=	${addprefix ${SRCDIR}, ${SRCNAME}}
OBJS	=	${SRCS:.c=.o}

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			${MAKE} -C ./libft
			cp libft/libft.a ${NAME}
			ar rcs ${NAME} ${OBJS}

all:		${NAME}

clean:		
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:	all clean fclean re