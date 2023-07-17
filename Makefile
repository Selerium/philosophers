# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/29 15:55:58 by jadithya          #+#    #+#              #
#    Updated: 2023/07/17 15:58:11 by jadithya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS := ${shell uname}

CC := cc

SRCDIR := src
OBJDIR := obj

NAME := philo

SRCS := $(SRCDIR)/philosophers.c\
		$(SRCDIR)/sim_utils.c\
		$(SRCDIR)/forks.c\
		$(SRCDIR)/check_args.c\
		$(SRCDIR)/philo_tasks.c\
		$(SRCDIR)/ft_atoi.c\
		$(SRCDIR)/run_sim.c\

OBJS := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

CFLAGS := -g3 -Wall -Wextra -Werror -pthread

all: $(NAME)

$(OBJDIR):
	mkdir -p obj

$(NAME): $(OBJS) $(OBJDIR)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJDIR)/*.o $(B_OBJDIR)/*.o

fclean: clean
	rm -f $(NAME) $(BONUS)

re: fclean all

norm:
	@echo "Mandatory:"
	@python3 -m norminette $(SRCS) include/philosophers.h

tests: $(NAME)
	./philo $(ARG)

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./philo $(ARG)

helgrind: $(NAME)
	valgrind --tool=helgrind ./philo $(ARG)

.PHONY: all clean fclean re norm tests valgrind helgrind