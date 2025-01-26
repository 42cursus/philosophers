# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abelov <abelov@student.42london.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/13 18:04:58 by abelov            #+#    #+#              #
#    Updated: 2024/09/13 18:04:59 by abelov           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= philo
CC				:= cc

OPTIMIZE_FLAGS	:= -O3
CC				:= cc
INCLUDE_FLAGS	:= -I. -I /usr/x86_64-linux-gnu/include
DEBUG_FLAGS		:= -g3 -gdwarf-3

MANDATORY_FLAGS	:= -Wall -Wextra -Werror

CFLAGS			= $(MANDATORY_FLAGS) $(OPTIMIZE_FLAGS)

LINK_FLAGS		:= -lpthread

CTAGS			:= ctags
RM				:= /bin/rm
RMFLAGS			:= -rfv

BUILD_DIR		= build
OBJDIR			= $(BUILD_DIR)/objs

SRCS	 		:= main.c \
					exec.c \
					init.c \
					monitor.c \
					parse.c \
					routine.c \
					status.c \
					ft_get_time.c \
					ft_isctype.c \
					ft_itoa.c \
					ft_memset.c \
					ft_strlen.c \
					ft_strtoul.c

OBJS			= $(SRCS:%.c=$(OBJDIR)/%.o)

# We need this for the output to go in the right place.  It will default to
# empty if make was configured to work with a cc that can't grok -c and -o
# together.  You can't compile the C library with such a compiler.
OUTPUT_OPTION	= -o $@

# https://make.mad-scientist.net/papers/advanced-auto-dependency-generation/
COMPILE.c		= $(CC) $(INCLUDE_FLAGS) $(CFLAGS) \
 					$(DEBUG_FLAGS) $(TARGET_ARCH) -c

all: $(NAME)

# make -p -R -r -f Makefile | grep -v '^#'
$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OUTPUT_OPTION) $^ $(LINK_FLAGS)

# "$<" Refers to the first prerequisite of the current target.
# "$^" Refers to all prerequisites of the current target, separated by spaces.
$(OBJDIR)/%.o : %.c
		@if [ ! -d $(@D) ]; then mkdir -p $(@D); fi
		@$(COMPILE.c) $(OUTPUT_OPTION) $<

clean:
		@$(RM) -rf $(BUILD_DIR) || true

fclean: clean
		@$(RM) $(RMFLAGS) $(NAME)

re: fclean all

.PHONY: clean fclean re
