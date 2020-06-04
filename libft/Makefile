# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnovotny < jnovotny@student.hive.fi>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/11 15:44:22 by jnovotny          #+#    #+#              #
#    Updated: 2019/12/27 18:24:52 by jnovotny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C_RED = \033[1;31m
C_GREEN = \033[1;32m
C_L_GREEN = \033[1;32m
C_BLUE = \033[1;34m
C_L_BLUE = \033[1;34m
C_WHITE = \033[1;37m
C_RES = \033[0m

NAME = libft.a

LIB = libft_srcs/

FTS =	datafeed.c \
		ft_printf.c \
		parsing.c \
		error.c \
		creator_hub.c \
		process_di.c \
		process_xx.c \
		process_o.c \
		process_b.c \
		process_u.c \
		process_f.c \
		process_c.c \
		process_s.c \
		process_p.c \
		flags_basic.c \
		no_convers.c \
		colors.c

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

FTO = $(FTS:.c=.o)
LIB_FTO = $(LIB_FTS:.c=.o)
ERROR_FTO = $(ERROR_FTS:.c=.o)
E_DIR = error_srcs/
S_DIR = pf_srcs/
O_DIR = ./objs/
I_DIR = -I./includes

SRCS = $(addprefix $(S_DIR), $(FTS))
SRCS += $(addprefix $(LIB), $(LIB_FTS))
SRCS += $(addprefix $(E_DIR), $(ERROR_FTS))
OBJS = $(addprefix $(O_DIR), $(FTO))
OBJS += $(addprefix $(O_DIR), $(LIB_FTO))
OBJS += $(addprefix $(O_DIR), $(ERROR_FTO))

CFLAGS = -Wall -Werror -Wextra

.PHONY: all clean fclean re

all: $(NAME)

$(OBJS):
	@/bin/mkdir -p $(O_DIR)
	@gcc $(CFLAGS) $(I_DIR) -c $(SRCS)
	@mv $(FTO) $(O_DIR)
	@mv $(LIB_FTO) $(O_DIR)
	@mv $(ERROR_FTO) $(O_DIR)

$(NAME): $(OBJS)
	@ar rcs $@ $^
	@ranlib $@
	@echo "$(C_GREEN)[Library Created!]$(C_RES)"

clean:
	@/bin/rm -rf $(O_DIR)
	@echo "$(C_RED)[Objects deleted!]$(C_RES)"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "$(C_RED)[Removed $(NAME)]$(C_RES)"

re: fclean all
