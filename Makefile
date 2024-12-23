# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/26 12:02:18 by fvizcaya          #+#    #+#              #
#    Updated: 2024/12/24 00:04:28 by fvizcaya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang 
CFLAGS = -Wall -Wextra -Werror -lpethread 

NAME = philo
SRC_DIR = src/

SRC = $(SRC_DIR)/actions.c
SRC += $(SRC_DIR)/arguments.c
SRC += $(SRC_DIR)/init.c
SRC += $(SRC_DIR)/main.c
SRC += $(SRC_DIR)/philo.c
SRC += $(SRC_DIR)/print.c
SRC += $(SRC_DIR)/time.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
	
re: fclean all

.PHONY: all clean fclean re bonus
