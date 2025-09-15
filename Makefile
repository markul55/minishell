# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/04 13:19:43 by wkozlows          #+#    #+#              #
#    Updated: 2025/09/14 12:00:00 by wkozlows         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = minishell
CC          = cc
LIBFT_DIR   = libft
CFLAGS      = -Wall -Wextra -Werror -g3 -I$(LIBFT_DIR)
LDFLAGS     = -L$(LIBFT_DIR) -lft -lreadline


SRCS        = main.c utils.c tokens.c commands.c exec.c
OBJS        = $(SRCS:.c=.o)

all: $(LIBFT_DIR)/libft.a $(NAME)

$(LIBFT_DIR)/libft.a:
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_DIR)/libft.a
	$(CC) $(CFLAGS) -o $@ $^ -L$(LIBFT_DIR) -lft -lreadline

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

debug: CFLAGS += -fsanitize=address,undefined
debug: re

.PHONY: all clean fclean re debug
