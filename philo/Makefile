# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mproveme <mproveme@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/08 10:40:08 by mproveme          #+#    #+#              #
#    Updated: 2022/07/09 20:53:03 by mproveme         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DIR		= 	src

SRCS	=	$(DIR)/ft_atoi.c \
			$(DIR)/ft_itoa.c \
			$(DIR)/lists_forks.c \
			$(DIR)/lists_philo.c \
			$(DIR)/philo.c \
			$(DIR)/print_action.c \
			$(DIR)/thread_create.c \
			$(DIR)/utils.c 

OBJS	= 	$(SRCS:.c=.o)

HEAD	=	header/philo.h

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -pthread

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
