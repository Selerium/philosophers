# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/29 15:55:58 by jadithya          #+#    #+#              #
#    Updated: 2023/07/12 16:06:41 by jadithya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS := ${shell uname}

CC := cc

SRCDIR := src
OBJDIR := obj
B_SRCDIR := bonussrcs
B_OBJDIR := bonusobjs

NAME := philo
BONUS := philo_bonus

SRCS := $(SRCDIR)/philosophers.c\
		$(SRCDIR)/check_args.c\
		$(SRCDIR)/ft_atoi.c\
		$(SRCDIR)/run_sim.c\
		$(SRCDIR)/sim_utils.c\

OBJS := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
B_SRCS := 
B_OBJS := $(B_SRCS:$(B_SRCDIR)/%.c=$(B_OBJDIR)/%.o)

CFLAGS := -g3 -Wall -Wextra -Werror -pthread

all: $(NAME)

bonus: $(BONUS)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(BONUS): $(B_OBJS)
	$(CC) $(CFLAGS) $(B_OBJS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(B_OBJS): $(B_SRCS)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJDIR)/*.o $(B_OBJDIR)/*.o

fclean: clean
	rm -f $(NAME) $(BONUS)

re: fclean all

norm:
	@echo "Mandatory:"
	@python3 -m norminette $(SRCS)
	@echo "Bonus:"
	@python3 -m norminette $(B_SRCS)

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./philo

.PHONY: all bonus clean fclean re norm valgrind