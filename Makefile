# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/26 12:02:18 by fvizcaya          #+#    #+#              #
#    Updated: 2025/02/06 20:56:33 by fvizcaya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -I . -g3

NAME = philo
SRC_DIR = src/

SRC = actions.c
SRC += arguments.c
SRC += dinner.c
SRC += fork_actions.c
SRC += init.c
SRC += main.c
SRC += philo.c
SRC += print.c
SRC += time.c

__SRC = $(addprefix $(SRC_DIR), $(SRC))
OBJ	= $(__SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lpthread -o $(NAME)

clean:
	rm -rf $(SRC_DIR)*.o

fclean: clean
	rm -rf $(NAME)
	
re: fclean all

.PHONY: all clean fclean re bonus
