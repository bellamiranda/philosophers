# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/21 13:44:52 by malves-b          #+#    #+#              #
#    Updated: 2024/10/10 14:54:55 by malves-b         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET = philo

FILES = $(wildcard srcs/*.c)

OBJS = $(patsubst srcs/%.c, objs/%.o, $(FILES))

CC = cc -g
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -f

all: create_objs $(TARGET)

create_objs:
	@mkdir -p objs

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

objs/%.o: srcs/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(TARGET)

re: fclean all

.PHONY: all, clean, fclean, re
