# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/04 17:08:23 by agrumbac          #+#    #+#              #
#    Updated: 2018/12/17 02:39:54 by agrumbac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

############################## VAR #############################################

NAME = libft.a

AS = nasm

ASFLAGS = -f macho64 -g

CC = clang

CFLAGS = -Wall -Wextra -Werror -O2 -Iincludes

############################## SRC #############################################

SRC_BTREE = \
	ft_btree_find.c ft_btree_iter.c ft_btree_del.c ft_btree_recursivedel.c

SRC_IO = \
	ft_cat.s ft_perr.s ft_putchar.s ft_puts.s ft_putstr.s

SRC_PRINTF = \
	ft_printf.c ft_printf_int.c ft_printf_str.c ft_printf_ptr.c \
	ft_printf_mod.c ft_printf_char.c ft_printf_padding.c ft_printf_itoa.c \
	ft_printf_buf.c

SRC_MATHS = \
	ft_abs.c ft_fac.c ft_intlen.c ft_sqrt.c ft_gcd.c ft_pow.c

SRC_MEM = \
	ft_bzero.s ft_memccpy.c ft_memcmp.c ft_memdel.c ft_memset.s \
	ft_memalloc.s ft_memchr.c ft_memcpy.s ft_memmove.c

SRC_STR = \
	ft_atoi.s ft_atoi_base.c ft_atol.c ft_atoll.s ft_isalnum.s ft_isalpha.s \
	ft_isascii.s ft_isdigit.s ft_isprint.s ft_isupper.c ft_isspace.c\
	ft_itoa_base_s.c \
	ft_strcat.s ft_strchr.s ft_strchrn.c ft_strclr.c ft_strcmp.c ft_strcpy.c \
	ft_strdup.s ft_strequ.c ft_striter.c ft_striteri.c ft_strlaststr.c \
	ft_strlcat.c ft_strlen.s ft_strncat.c ft_strncmp.s ft_strncpy.s \
	ft_strnequ.c ft_strnlen.c ft_strnstr.c ft_strrchr.c ft_strstr.c \
	ft_strtolower.c ft_strtoupper.c ft_tolower.s ft_toupper.s ft_wcslen.c

SRC = \
	$(addprefix srcs/ft_io/, ${SRC_IO}) \
	$(addprefix srcs/ft_io/ft_printf/, ${SRC_PRINTF}) \
	$(addprefix srcs/ft_btree/, ${SRC_BTREE}) \
	$(addprefix srcs/ft_maths/, ${SRC_MATHS}) \
	$(addprefix srcs/ft_mem/, ${SRC_MEM}) \
	$(addprefix srcs/ft_str/, ${SRC_STR})

COBJ = $(SRC:.c=.o)

OBJ = $(COBJ:.s=.o)

############################## COLORS ##########################################

R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
X = "\033[0m"

############################## BUILD ###########################################

.SILENT:

all: ${NAME}

${NAME}: ${OBJ}
	@echo ${B}Compiling" "[${NAME}]...${X}
	ar rcs ${NAME} ${OBJ}
	@echo ${G}Success"   "[${NAME}]${X}

############################## MORE ############################################

clean:
	@echo ${R}Cleaning"  "[objs]...${X}
	/bin/rm -f ${OBJ}

fclean: clean
	@echo ${R}Cleaning"  "[${NAME}]...${X}
	/bin/rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
