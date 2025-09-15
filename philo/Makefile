# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/07 08:54:59 by ssadi-ou          #+#    #+#              #
#    Updated: 2025/09/11 19:52:31 by ssadi-ou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra -pthread -g

SRCS =     philosophers.c \
	   utils.c \
	   parsing.c \
	   safe_functions.c \
	   all_inits.c \
	   simulation.c \
	   anti_data_races.c \
	   print.c \
	   monitor.c \
	   utils_2.c \

OBJS    := $(SRCS:.c=.o)

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
