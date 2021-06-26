# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/23 20:10:15 by ybouddou          #+#    #+#              #
#    Updated: 2021/06/26 11:31:35 by ybouddou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = sudoku
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIB = Libft/libft.a

SRC =	sudoku.c\
		printing.c\
		tools.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(LIB) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $^ -o $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all