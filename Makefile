# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pauvicto <pauvicto@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/02 18:38:23 by pauvicto          #+#    #+#              #
#    Updated: 2023/08/15 00:57:59 by pauvicto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Wextra -Werror -pthread

RM = rm -rf

SRCS = 	error_handler.c\
		init_handler.c\
		main.c\
		philo_handler.c\
		utils.c

$(NAME) :
	gcc $(CFLAGS) $(SRCS) -o $(NAME)

all : $(NAME)

fclean : clean
	$(RM) $(NAME)

clean :
	$(RM) $(NAME)

re : fclean all
