# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/10 07:28:53 by alevasse          #+#    #+#              #
#    Updated: 2022/12/12 12:53:24 by alevasse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= philo

SRC 			= 	src/main.c src/init.c src/thread.c src/utils.c src/utils_2.c \
					src/death.c


OBJ 			= ${SRC:.c=.o}
				
CC 				= gcc -g
CFLAGS 			= -Wall -Wextra -Werror -fsanitize=thread

AR 				= ar rcs
RM 				= rm -f

GREEN			:= "\033[0;32m"
CYAN			:= "\033[0;36m"
RESET			:= "\033[0m"

%.o:			%.c
				@${CC} ${CFLAGS} -o $@ -c $<

all: 			${NAME}

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