# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/29 15:55:58 by jadithya          #+#    #+#              #
#    Updated: 2023/06/29 20:59:43 by jadithya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS := ${shell uname}

NAME := philo
BONUS := philo_bonus

CC := cc
CFLAGS := -g3 -Wall -Wextra -Werror -lpthread
LIB := libft/libft.a

SRCDIR := srcs
B_SRCDIR := bonussrcs
OBJDIR := objs
B_OBJDIR := bonusobjs

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(subst $(SRCDIR), $(OBJDIR), $(SRCS:.c=.o))
B_SRCS = $(wildcard $(B_SRCDIR)/*.c)
B_OBJS = $(subst $(B_SRCDIR), $(B_OBJDIR), $(B_SRCS:.c=.o))

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -o $@ -c $<

$(B_OBJS): $(B_SRCS)
	$(CC) $(CFLAGS) -o $@ -c $<

$(LIB):
	make bonus -C libft

$(NAME): $(LIB) $(OBJS)
	$(CC) $(OBJS) -o $@ $(CFLAGS) $(LIB)

$(BONUS): $(LIB) $(B_OBJS)
	$(CC) $(B_OBJS) -o $@ $(CFLAGS) $(LIB)

.PHONY: all bonus clean fclean re norm valgrind

all: $(NAME)

bonus: $(BONUS)

clean:
	rm -f $(OBJDIR)/*.o $(B_OBJDIR)/*.o
	make clean -C libft

fclean: clean
	rm -f $(NAME) $(BONUS)
	rm -f libft/libft.a

re: fclean all

norm:
	@echo "Mandatory: \n"
	python3 -m norminette $(SRCS)
	@echo "Bonus: \n"
	python3 -m norminette $(B_SRCS)

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./philo
