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

#MANDATORY_FLAGS	:= -Wall -Wextra -Werror
MANDATORY_FLAGS	:= -Wall -Wextra -Werror -Wwrite-strings -Wimplicit
CFLAGS			= $(MANDATORY_FLAGS) $(OPTIMIZE_FLAGS)

LIBFT_PATH		=  ./lib/ft
LIBFT			=  $(LIBFT_PATH)/libft.a

LINK_FLAGS		:= -L $(LIBFT_PATH) -lft -lpthread

CTAGS			:= ctags
RM				:= /bin/rm
RMFLAGS			:= -rfv

BUILD_DIR		= build
OBJDIR			= $(BUILD_DIR)/objs
DEPDIR			= $(BUILD_DIR)/deps

SRC_DIR			= src
SRC_FS	 		:= main.c

SRCS	 		:= $(SRC_FS:%.c=$(SRC_DIR)/%.c)
OBJS			= $(SRCS:$(SRC_DIR)/%.c=$(OBJDIR)/%.o)
DEPS			= $(SRCS:$(SRC_DIR)/%.c=$(DEPDIR)/%.d)

# We need this for the output to go in the right place.  It will default to
# empty if make was configured to work with a cc that can't grok -c and -o
# together.  You can't compile the C library with such a compiler.
OUTPUT_OPTION	= -o $@

# https://make.mad-scientist.net/papers/advanced-auto-dependency-generation/
COMPILE.c		= $(CC) $(INCLUDE_FLAGS) $(DEPFLAGS) $(CFLAGS) \
 					$(DEBUG_FLAGS) $(TARGET_ARCH) -c

LIBFT_PREFIX	= $(LIBFT_PATH)/
include $(LIBFT_PATH)/libft.mk

LIBFT_DEPS		= $(FT_SRCS:%.c=$(LIBFT_PATH)/build/deps/%.d)

all: $(LIBFT) $(PROGRAM)

# Include dependency files
-include $(DEPS)
-include $(LIBFT_DEPS)

$(LIBFT): $(LIBFT_PATH)/Makefile
		@$(MAKE) -C $(LIBFT_PATH) -j8

# make -p -R -r -f Makefile | grep -v '^#'
$(PROGRAM): $(OBJS) $(LIBFT)
		$(CC) $(CFLAGS) $(OUTPUT_OPTION) $^ $(LINK_FLAGS)

$(DEPS):

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
