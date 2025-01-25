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

PROGRAM			:= philosophers
CC				:= cc
INC_DIR			=  ./include
INCLUDE_FLAGS	:= -I. -I $(INC_DIR) -I /usr/x86_64-linux-gnu/include

OPTIMIZE_FLAGS	:= -O0
CC				:= cc
INCLUDE_FLAGS	:= -I. -I./include -I./include/ft
DEBUG_FLAGS		:= -g3 -gdwarf-3
DEPFLAGS		= -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

MANDATORY_FLAGS	:= -Wall -Wextra -Werror
#MANDATORY_FLAGS	:= -Wall -Wextra -Werror -Wwrite-strings -Wimplicit
CFLAGS			= $(MANDATORY_FLAGS) $(OPTIMIZE_FLAGS)

LINK_FLAGS		:= -lpthread

CTAGS			:= ctags
RM				:= /bin/rm
RMFLAGS			:= -rfv

BUILD_DIR		= build
OBJDIR			= $(BUILD_DIR)/objs
DEPDIR			= $(BUILD_DIR)/deps

SRC_DIR			= src
UTILS_DIR		= utils
SRC_FS	 		:= main.c \
					exec.c \
					init.c \
					monitor.c \
					parse.c \
					routine.c \
					status.c

UTILS_FS 		:= ft_get_time.c \
					ft_isctype.c \
					ft_isctype2.c \
					ft_itoa.c \
					ft_mem.c \
					ft_memset.c \
					ft_perror.c \
					ft_strlen.c \
					ft_strtol.c \
					ft_strtoul.c \


SRCS	 		:= $(SRC_FS:%.c=$(SRC_DIR)/%.c)
SRCS	 		+= $(UTILS_FS:%.c=$(SRC_DIR)/$(UTILS_DIR)/%.c)
OBJS			= $(SRCS:$(SRC_DIR)/%.c=$(OBJDIR)/%.o)
DEPS			= $(SRCS:$(SRC_DIR)/%.c=$(DEPDIR)/%.d)

# We need this for the output to go in the right place.  It will default to
# empty if make was configured to work with a cc that can't grok -c and -o
# together.  You can't compile the C library with such a compiler.
OUTPUT_OPTION	= -o $@

# https://make.mad-scientist.net/papers/advanced-auto-dependency-generation/
COMPILE.c		= $(CC) $(INCLUDE_FLAGS) $(DEPFLAGS) $(CFLAGS) \
 					$(DEBUG_FLAGS) $(TARGET_ARCH) -c

all: $(PROGRAM)

# make -p -R -r -f Makefile | grep -v '^#'
$(PROGRAM): $(OBJS)
		$(CC) $(CFLAGS) $(OUTPUT_OPTION) $^ $(LINK_FLAGS)

# "$<" Refers to the first prerequisite of the current target.
# "$^" Refers to all prerequisites of the current target, separated by spaces.
$(OBJDIR)/%.o : $(SRC_DIR)/%.c
$(OBJDIR)/%.o : $(SRC_DIR)/%.c $(DEPDIR)/%.d
		@if [ ! -d $(@D) ]; then \
  			mkdir -p $(@D); \
			mkdir -p $(@D:$(OBJDIR)%=$(DEPDIR)%); fi
		@$(COMPILE.c) $(OUTPUT_OPTION) $<

.PHONY: clean fclean re

clean:
		@$(RM) -rf $(BUILD_DIR) || true
		@$(MAKE) -s -C $(LIBFT_PATH) clean

fclean: clean
		@$(RM) $(RMFLAGS) $(NAME)
		@$(MAKE) -s -C $(LIBFT_PATH) fclean

re: fclean all
