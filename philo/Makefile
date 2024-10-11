# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/06 01:32:20 by nmatondo          #+#    #+#              #
#    Updated: 2024/08/07 16:44:49 by nmatondo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = ./philo
SRC = ./src/
INCLUDE = ./include
FILES = philo.c \
		philo_utils_1.c \
		philo_time.c \
		philo_operations.c \
		philo_init_and_free.c \
		philo_take_fork.c \

SRC_FILES = $(addprefix $(SRC),$(FILES))
OBJ = $(FILES:.c=.o)

FLAGS = -Wall -Wextra -Werror
PLIBFT = ./libft

all:    $(NAME)

$(NAME):
	$(CC) $(FLAGS) -c $(SRC_FILES) -I$(INCLUDE)
	@$(CC) $(FLAGS) $(OBJ) -I$(INCLUDE) -o $(NAME)

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)


re:     fclean all

.PHONY: all bonus clean fclean re
