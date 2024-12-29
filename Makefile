# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/26 12:02:18 by fvizcaya          #+#    #+#              #
#    Updated: 2024/12/29 21:55:03 by fvizcaya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang 
CFLAGS = -Wall -Wextra -Werror -lpthread 

NAME = philo
SRC_DIR = src

SRC = actions.c
SRC += arguments.c
SRC += dinner.c
SRC += fork_actions.c
SRC += init.c
SRC += main.c
SRC += philo.c
SRC += print.c
SRC += time.c

OBJ := $(patsubst $(SRC_DIR)%.,$(SRC_DIR)%.o,$(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)
	
re: fclean all

.PHONY: all clean fclean re bonus
