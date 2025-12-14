# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtoky-fa <rtoky-fa@student.42antanana      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/06 10:58:18 by rtoky-fa          #+#    #+#              #
#    Updated: 2025/03/18 15:49:09 by rtoky-fa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=	libft.a
SOURCE=	ft_isalnum.c\
		ft_isprint.c\
		ft_memmove.c\
		ft_strlcat.c\
		ft_strnstr.c\
		ft_atoi.c\
		ft_isalpha.c\
		ft_memchr.c\
		ft_memset.c\
		ft_strlcpy.c\
		ft_strrchr.c\
		ft_bzero.c\
		ft_isascii.c\
		ft_memcmp.c\
		ft_strchr.c\
		ft_strlen.c\
		ft_tolower.c\
		ft_calloc.c\
		ft_isdigit.c\
		ft_memcpy.c\
		ft_strdup.c\
		ft_strncmp.c\
		ft_toupper.c\
		ft_substr.c\
		ft_putchar_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_putstr_fd.c\
		ft_strmapi.c\
		ft_striteri.c\
		ft_strjoin.c\
		ft_strtrim.c\
		ft_itoa.c\
		ft_split.c\

OBJS= ${SOURCE:.c=.o}

CC=		gcc
FLAG=	-Wall -Wextra -Werror

all: $(NAME)
	
$(NAME): $(OBJS)
	ar -crs $(NAME) $(OBJS)
%.o: %.c
	$(CC) $(FLAG) -c $< -o $@
clean:
		rm -f $(OBJS)
fclean:clean
		rm -f $(NAME)
re:fclean all

.PHONY: all clean fclean re
