# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/07 13:07:53 by mchardin          #+#    #+#              #
#    Updated: 2021/12/11 13:35:44 by mchardin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PREFIX		=	./srcs/

INCLUDES	=	./includes/

SRCS		=	$(addprefix $(PREFIX), \
								main.c \
								utils.c \
								map_utils.c \
								element_utils.c \
								map_insert.c \
								gnl.c \
								)

OBJS		=	${SRCS:.c=.o}

DEPS		=	${OBJS:.o=.d}

CC			=	cc

CFLAGS		=	-Werror -Wextra -Wall -I ${INCLUDES} -MMD

NAME 		=	hotrace

RM			=	rm -f

all:
			${MAKE} ${NAME}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

run:		all
			./$(NAME) < test_file

clean:
			${RM} ${OBJS}
			${RM} ${DEPS}

fclean:
			${RM} ${OBJS}
			${RM} ${DEPS}
			${RM} ${NAME}

re:			fclean all

.PHONY: 	all re run clean fclean

-include	${DEPS}