# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvizcaya <fvizcaya@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/26 12:02:18 by fvizcaya          #+#    #+#              #
#    Updated: 2024/07/05 12:31:15 by fvizcaya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang 
CFLAGS = -Wall -Wextra -Werror -g

NAME = push_swap
LIBFT_DIR = libft/
LIBFT = libft.a
BONUS_DIR = checker/
SRC = \
	arguments_parsing.c arguments_validation.c find_positions.c main.c movements.c \
	push_swap.c rotate_movements.c rotate_to_head.c order_checking.c \
	set_indexes.c sort_small_sizes.c stack.c utils.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

bonus:
	make -C $(BONUS_DIR)

$(NAME): $(OBJ)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_DIR)$(LIBFT) -o $(NAME)

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(BONUS_DIR)
	rm -rf $(OBJ)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(BONUS_DIR)
	rm -rf $(NAME)
	
re: fclean all

.PHONY: all clean fclean re bonus
