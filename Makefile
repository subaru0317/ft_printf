NAME	=	libftprintf.a
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
SRCDIR	=	./
SRCNAME	=	ft_printf.c libft_extend_utils.c math_utils.c read_pointer.c read_int.c read_literal.c set_options.c read_hex_num.c
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
			${MAKE} -C ./libft clean
			${RM} ${OBJS}

fclean:		clean
			${MAKE} -C ./libft fclean
			${RM} ${NAME}

re:			fclean all

.PHONY:	all clean fclean re