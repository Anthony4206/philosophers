# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/10 07:28:53 by alevasse          #+#    #+#              #
#    Updated: 2022/08/26 08:28:01 by alevasse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= philo

SRC 			= src/main.c src/init.c src/thread.c

SRC_B 			=

OBJ 			= ${SRC:.c=.o}
OBJ_B 			= ${SRC_B:.c=.o}
				
CC 				= gcc -g
CFLAGS 			= -Wall -Wextra -Werror #-fsanitize=address

AR 				= ar rcs
RM 				= rm -f

GREEN			:= "\033[0;32m"
CYAN			:= "\033[0;36m"
RESET			:= "\033[0m"

%.o:			%.c
				@${CC} ${CFLAGS} -o $@ -c $<

all: 			${NAME}

bonus:			${OBJ_B} ${HEAD}
				@${CC} ${CFLAGS} -o ${NAME} ${OBJ_B}
				@echo ${GREEN}"Compiled '${NAME}' with success" ${RESET}
				@touch bonus

${NAME}:		${OBJ} ${HEAD}
				@${CC} ${CFLAGS} -o ${NAME} ${OBJ}
				@echo ${GREEN}"Compiled '${NAME}' with success" ${RESET}

clean:
				@${RM} ${OBJ} ${OBJ_B}
				@echo ${CYAN}"Cleaned '${NAME}' objects with success"${RESET}
				
fclean:			clean
				@${RM} ${NAME} ${NAME_B}
				@echo ${CYAN}"Removed '${NAME}' with success"${RESET}

re:				fclean all

.PHONY: 		all clean fclean re