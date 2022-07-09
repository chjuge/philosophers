# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mproveme <mproveme@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/08 10:40:08 by mproveme          #+#    #+#              #
#    Updated: 2022/07/08 10:40:13 by mproveme         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DIR		= 	src

SRCS	=	$(DIR)

OBJS	= 	$(SRCS:.c=.o)

HEAD	=	header/philo.h

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror 

RM		=	rm -rf

NAME	=	philo

all:		$(NAME)

%.o:		%.c	$(HEAD) 
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS) $(HEAD) 
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:		
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re 
