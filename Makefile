# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/04 16:41:34 by jnovotny          #+#    #+#              #
#    Updated: 2020/07/20 16:28:59 by jnovotny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Targets
ASM_EXEC = asm
VM_EXEC = corewar
DEASM_EXEC = deasm

# GCC Settings
CC = gcc
CFLAGS = 
LDFLAGS = $(LIBFT_FLAG)
INCLUDES = -I includes/ $(LIBFT_INC)

# ASM Sources
ASM_DIR = asm/
ASM_FILES =	asm.c \
			cleanup.c \
			encoding.c \
			check_operations.c \
			filename_util.c \
			init.c \
			print_debug.c \
			analysis.c \
			to_bytecode.c \
			write_header.c \
			write_helper.c \
			write_exec_code.c \
			arg_math.c \
			special_args.c

ASM_SRC = $(addprefix $(ASM_DIR), $(ASM_FILES))

# DEASM Sources
DEASM_DIR = deasm/
DEASM_FILES =	deasm.c \
				decode.c \
				read.c \
				init_clean.c \
				utils.c \
				write.c

DEASM_SRC = $(addprefix $(DEASM_DIR), $(DEASM_FILES))

# CoreWar Sources
VM_DIR = vm/
VM_FILES =	arena.c \
			carriage.c \
			champs.c \
			debug_utils.c \
			decode.c \
			engine.c \
			init_colors.c \
			log.c \
			visual.c \
			vm.c \
			vm_args.c \
			op/op12_fork.c \
			op/op16_aff.c \
			op/op14.lldi.c \
			op/op13_lld.c \
			op/op15_lfork.c \
			op/op05_sub.c \
			op/op06_and.c \
			op/op08_xor.c \
			op/op02_ld.c \
			op/op07_or.c \
			op/op10_ldi.c \
			op/op11_sti.c \
			op/op04_add.c \
			op/op03_st.c \
			op/op09_zjmp.c \
			op/op01_live.c

VM_SRC = $(addprefix $(VM_DIR), $(VM_FILES))

# Libraries
LIBS_DIR = lib/

## LibFT
LIBFT_DIR = $(LIBS_DIR)libft/
LIBFT_INC = -I $(LIBFT_DIR)includes/
LIBFT = $(LIBFT_DIR)libft.a
LIBFT_FLAG = -L $(LIBFT_DIR) -lft

# Directories and Objects Settings
SRC_DIR = sources/
OBJ_DIR = objects/

TARGET_DIR = $(OBJ_DIR)
TARGET_DIR += $(addprefix $(OBJ_DIR), $(ASM_DIR) $(VM_DIR) $(DEASM_DIR) $(VM_DIR)/op)

ASM_FTO = $(ASM_SRC:.c=.o)
ASM_OBJ = $(addprefix $(OBJ_DIR), $(ASM_FTO))

VM_FTO = $(VM_SRC:.c=.o)
VM_OBJ = $(addprefix $(OBJ_DIR), $(VM_FTO))

DEASM_FTO = $(DEASM_SRC:.c=.o)
DEASM_OBJ = $(addprefix $(OBJ_DIR), $(DEASM_FTO))

# Colors
C_RED = \033[1;31m
C_GREEN = \033[1;32m
C_L_GREEN = \033[1;32m
C_BLUE = \033[1;34m
C_L_BLUE = \033[1;34m
C_WHITE = \033[1;37m
C_EOC = \033[0m

# Tools and Utilities
PROG_BAR = "$(C_RED)▒$(C_EOC)"
LFT_BAR = "▒"
LOGO = yes
LFT_ARG = LOGO=no STATUS=no PROGRESS_CHAR=$(LFT_BAR)
FIRST = yes

.PHONY: all clean fclean re

all: $(ASM_EXEC) $(VM_EXEC) $(DEASM_EXEC)
	@echo "\n$(C_GREEN)Finished compiling! Enjoy the bloodbath!$(C_EOC)"

logo:
ifeq (yes, $(LOGO))
	@echo "$(C_RED) ▄████▄   ▒█████   ██▀███  ▓█████  █     █░ ▄▄▄       ██▀███  $(C_EOC)"
	@echo "$(C_RED)▒██▀ ▀█  ▒██▒  ██▒▓██ ▒ ██▒▓█   ▀ ▓█░ █ ░█░▒████▄    ▓██ ▒ ██▒$(C_EOC)"
	@echo "$(C_RED)▒▓█    ▄ ▒██░  ██▒▓██ ░▄█ ▒▒███   ▒█░ █ ░█ ▒██  ▀█▄  ▓██ ░▄█ ▒$(C_EOC)"
	@echo "$(C_RED)▒▓▓▄ ▄██▒▒██   ██░▒██▀▀█▄  ▒▓█  ▄ ░█░ █ ░█ ░██▄▄▄▄██ ▒██▀▀█▄  $(C_EOC)"
	@echo "$(C_RED)▒ ▓███▀ ░░ ████▓▒░░██▓ ▒██▒░▒████▒░░██▒██▓  ▓█   ▓██▒░██▓ ▒██▒$(C_EOC)"
	@echo "$(C_RED)░ ░▒ ▒  ░░ ▒░▒░▒░ ░ ▒▓ ░▒▓░░░ ▒░ ░░ ▓░▒ ▒   ▒▒   ▓▒█░░ ▒▓ ░▒▓░$(C_EOC)"
	@echo "$(C_RED)  ░  ▒     ░ ▒ ▒░   ░▒ ░ ▒░ ░ ░  ░  ▒ ░ ░    ▒   ▒▒ ░  ░▒ ░ ▒░$(C_EOC)"
	@echo "$(C_RED)░        ░ ░ ░ ▒    ░░   ░    ░     ░   ░    ░   ▒     ░░   ░ $(C_EOC)"
	@echo "$(C_RED)░ ░          ░ ░     ░        ░  ░    ░          ░  ░   ░     $(C_EOC)"
	@echo "$(C_RED)░                                                             $(C_EOC)"
	@echo "\n"
LOGO = no
endif

$(TARGET_DIR): logo
	@mkdir -p $(TARGET_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<
	@echo $(PROG_BAR)"\c"

$(LIBFT):
	@echo "\n[Compiling LibFT]"
	@make -C $(LIBFT_DIR) $(LFT_ARG)
	@echo "\n[Done]"
	@echo "\n[Compiling into object files]"

$(ASM_EXEC): $(TARGET_DIR) $(LIBFT) $(ASM_OBJ)
	@echo "\n[ASM Object files ready]"
	@echo "[Linking Assembler executable]"
	@$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDES) -o $@ $(ASM_OBJ)
	@echo "[Done]"

$(VM_EXEC): $(TARGET_DIR) $(LIBFT) $(VM_OBJ)
	@echo "\n[VM Object files ready]"
	@echo "[Linking Virtul Machine executable]"
	@$(CC) $(CFLAGS) $(LDFLAGS) -lncurses $(INCLUDES) -o $@ $(VM_OBJ)
	@echo "[Done]"
	
$(DEASM_EXEC): $(TARGET_DIR) $(LIBFT) $(DEASM_OBJ)
	@echo "\n[DEASM Object files ready]"
	@echo "[Linking DeAssembler executable]"
	@$(CC) $(CFLAGS) $(LDFLAGS) -lncurses $(INCLUDES) -o $@ $(DEASM_OBJ)
	@echo "[Done]"

clean: logo
	@make clean -C $(LIBFT_DIR) $(LFT_ARG)
	@/bin/rm -rf $(OBJ_DIR)
	@echo "\n$(C_RED)[Objects Obliterated!]$(C_EOC)"

fclean: clean
	@make fclean -C $(LIBFT_DIR) $(LFT_ARG)
	@/bin/rm -rf $(ASM_EXEC)
	@/bin/rm -rf $(VM_EXEC)
	@/bin/rm -rf $(DEASM_EXEC)
	@echo "$(C_RED)[Executables $(ASM_EXEC), $(DEASM_EXEC) and $(VM_EXEC) have been utterly vaporized!]$(C_EOC)"

re: fclean all
