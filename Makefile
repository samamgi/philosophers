# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/07 08:54:59 by ssadi-ou          #+#    #+#              #
#    Updated: 2025/09/10 21:26:43 by ssadi-ou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers

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
	   libft/ft_atoi.c libft/ft_bzero.c libft/ft_calloc.c libft/ft_isalnum.c \
           libft/ft_isalpha.c libft/ft_isascii.c libft/ft_isdigit.c libft/ft_isprint.c \
           libft/ft_memchr.c libft/ft_memcmp.c libft/ft_memcpy.c libft/ft_memmove.c \
           libft/ft_memset.c libft/ft_strchr.c libft/ft_strdup.c libft/ft_strlcat.c \
           libft/ft_strlcpy.c libft/ft_strlen.c libft/ft_strncmp.c libft/ft_strnstr.c \
           libft/ft_strrchr.c libft/ft_tolower.c libft/ft_toupper.c \
           libft/ft_itoa.c libft/ft_putchar_fd.c libft/ft_putendl_fd.c libft/ft_putnbr_fd.c \
           libft/ft_putstr_fd.c libft/ft_split.c libft/ft_strjoin.c libft/ft_strmapi.c \
           libft/ft_strtrim.c libft/ft_substr.c libft/ft_striteri.c libft/ft_printf.c \
           libft/ft_printf_else.c libft/ft_printf_hex.c libft/ft_printf_nbr.c \
           libft/ft_lstadd_back_bonus.c libft/ft_lstadd_front_bonus.c libft/ft_lstmap_bonus.c \
           libft/ft_lstlast_bonus.c libft/ft_lstclear_bonus.c libft/ft_lstiter_bonus.c \
           libft/ft_lstnew_bonus.c libft/ft_lstsize_bonus.c libft/ft_lstdelone_bonus.c

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
