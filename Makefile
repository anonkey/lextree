# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tseguier <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/10/19 20:08:00 by tseguier          #+#    #+#              #
#    Updated: 2014/10/24 18:22:56 by tseguier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


ifeq ($(GCC), 1)
	CC = gcc
else
	CC = clang
endif
ifeq ($(DEBUG), 1)
	CFLAGS = -Wall -Wextra -Werror -ggdb3
else
	CFLAGS = -Wall -Wextra -Werror -ggdb3
endif
NAME = lextree
INCDIR = ./libft/headers
LIBDIR = ./libft/
LIBNAME = libft
LIB = -lft
SRC = ft_tabcpy.c \
ft_tabdel.c \
ft_tabncpy.c \
ft_tabrealloc.c \
main.c
OBJ = $(SRC:.c=.o)

all: $(LIBNAME) $(NAME)

$(LIBNAME):
	make -C $(LIBDIR)

$(LIBNAME)_fclean:
	make -C $(LIBDIR) fclean

gcc: $(OBJ)
	gcc $(CFLAGS) $(OBJ) -o $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -L$(LIBDIR) $(LIB) $(OBJ) -o $(NAME) -I $(INCDIR)
%.o: %.c
	$(CC) -I$(LIBDIR) $(CFLAGS) -c $< -o $@ -I $(INCDIR)

clean:
	rm -rf $(OBJ)

fclean: $(LIBNAME)_fclean clean
	rm -rf $(NAME)

re: $(LIBNAME)_fclean fclean all

.PHONY: $(LIBNAME) $(LIBNAME)_fclean clean fclean all re