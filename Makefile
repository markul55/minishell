# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/04 13:19:43 by wkozlows          #+#    #+#              #
#    Updated: 2025/08/04 13:19:43 by wkozlows         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# === VARIABLES ===
NAME    = minishell
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I$(LIBFT_DIR)

SRCS    = main.c utils.c
OBJS    = $(SRCS:.c=.o)

# === LIBFT ===
LIBFT_DIR = libft
LIBFT_A   = $(LIBFT_DIR)/libft.a

# === READLINE ===
RLFLAGS = -lreadline -lncurses

# === BUILD ===
all: $(LIBFT_A) $(NAME)

$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_A) $(RLFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_A):
	make -C $(LIBFT_DIR)

# === CLEAN ===
clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
