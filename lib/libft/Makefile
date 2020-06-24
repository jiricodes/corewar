# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/11 15:44:22 by jnovotny          #+#    #+#              #
#    Updated: 2020/06/08 18:34:02 by jnovotny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name
NAME = libft.a

# Source Files
PRINTF_FTS =	ft_printf.c \
		converts.c \
		help.c \
		parse_color.c \
		parse_funcs.c \
		parser.c \
		str_maker.c \
		utils.c \
		make_float.c \
		c_op.c \
		di_op.c \
		f_op.c \
		p_op.c \
		str_op.c \
		uox_op.c 

LIB_FTS = ft_atoi.c \
		ft_latoi.c \
		ft_base_len.c \
		ft_bzero.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_isspace.c \
		ft_itoa.c \
		ft_itoa_base.c \
		ft_lstadd.c \
		ft_lstdel.c \
		ft_lstdelone.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_lstnew.c \
		ft_ltoa.c \
		ft_ltoa_base.c \
		ft_memalloc.c \
		ft_memccpy.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memdel.c \
		ft_memmove.c \
		ft_memset.c \
		ft_min_sqrt.c \
		ft_power.c \
		ft_power_l.c \
		ft_putchar.c \
		ft_putchar_fd.c \
		ft_putendl.c \
		ft_putendl_fd.c \
		ft_putnbr.c \
		ft_putnbr_fd.c \
		ft_putstr.c \
		ft_putstr_fd.c \
		ft_realloc.c \
		ft_strcat.c \
		ft_strchr.c \
		ft_strclr.c \
		ft_strcmp.c \
		ft_strcpy.c \
		ft_strdel.c \
		ft_strdup.c \
		ft_strendwith.c \
		ft_strequ.c \
		ft_striter.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlen.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strncat.c \
		ft_strncmp.c \
		ft_strncpy.c \
		ft_strnequ.c \
		ft_strnew.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strset.c \
		ft_strsplit.c \
		ft_strstr.c \
		ft_strsub.c \
		ft_strtrim.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_uitoa.c \
		ft_uitoa_base.c \
		ft_ultoa.c \
		ft_ultoa_base.c \
		ft_lftoa.c \
		get_next_line.c

ERROR_FTS =	ft_error_exit.c

# Folders
SRC_DIR = sources/
LIB_DIR = libft_srcs/
ERROR_DIR = error_srcs/
PRINTF_DIR = jani_pf_srcs/
OBJ_DIR = ./object_files/
INCLUDES_DIR = -I./includes
TARGET_DIRS = $(OBJ_DIR)
TARGET_DIRS += $(addprefix $(OBJ_DIR), $(LIB_DIR) $(ERROR_DIR) $(PRINTF_DIR))

# Pathing
PRINTF_SRCS = $(addprefix $(PRINTF_DIR), $(PRINTF_FTS))
LIB_SRCS = $(addprefix $(LIB_DIR), $(LIB_FTS))
ERROR_SRCS = $(addprefix $(ERROR_DIR), $(ERROR_FTS))

PRINTF_FTO = $(PRINTF_SRCS:.c=.o)
LIB_FTO = $(LIB_SRCS:.c=.o)
ERROR_FTO = $(ERROR_SRCS:.c=.o)

OBJS = $(addprefix $(OBJ_DIR), $(PRINTF_FTO) $(LIB_FTO) $(ERROR_FTO))

CFLAGS = -Wall -Werror -Wextra

# Colors
C_RED = \033[1;31m
C_GREEN = \033[1;32m
C_L_GREEN = \033[1;32m
C_BLUE = \033[1;34m
C_L_BLUE = \033[1;34m
C_WHITE = \033[1;37m
C_RES = \033[0m

# Tools and Utils
LOGO = yes
COMP = yes
STATUS = yes
PROGRESS_CHAR = "*"

.PHONY: all clean fclean re

all: $(NAME)

logo:
ifeq (yes, $(LOGO))
	@echo "$(C_BLUE) _     _ _    ______ _____ $(C_RES)"
	@echo "$(C_BLUE)| |   (_) |   |  ___|_   _|$(C_RES)"
	@echo "$(C_BLUE)| |    _| |__ | |_    | |  $(C_RES)"
	@echo "$(C_BLUE)| |   | | '_ \|  _|   | |  $(C_RES)"
	@echo "$(C_BLUE)| |___| | |_) | |     | |  $(C_RES)"
	@echo "$(C_BLUE)\_____/_|_.__/\_|     \_/  $(C_RES)"
	@echo "\n"
LOGO = no
endif

$(TARGET_DIRS): logo
	@/bin/mkdir -p $(OBJ_DIR)
	@/bin/mkdir -p $(OBJ_DIR)$(LIB_DIR)
	@/bin/mkdir -p $(OBJ_DIR)$(ERROR_DIR)
	@/bin/mkdir -p $(OBJ_DIR)$(PRINTF_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@gcc $(CFLAGS) $(INCLUDES_DIR) -o $@ -c $<
	@echo $(PROGRESS_CHAR)"\c"

$(NAME): $(TARGET_DIRS) $(OBJS)
	@ar rcs $@ $(OBJS)
	@ranlib $@
ifeq (yes, $(STATUS))
	@echo "$(C_GREEN)\n[Library Created!]$(C_RES)"
endif

clean: logo
	@/bin/rm -rf $(OBJ_DIR)
ifeq (yes, $(STATUS))
	@echo "$(C_RED)[Objects deleted!]$(C_RES)"
endif

fclean: clean
	@/bin/rm -f $(NAME)
ifeq (yes, $(STATUS))
	@echo "$(C_RED)[Removed $(NAME)]$(C_RES)"
endif

re: fclean all
