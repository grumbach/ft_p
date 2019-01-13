# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/10 17:19:11 by agrumbac          #+#    #+#              #
#    Updated: 2019/01/13 19:38:53 by agrumbac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

############################## BIN #############################################

SERVER_NAME = server

CLIENT_NAME = client

CC = gcc

CFLAGS = -Wall -Wextra -Werror -MMD

COMMON_SRC = socket.c errors.c socket_io.c file_io.c basic_parsing.c

SERVER_SRC = ${COMMON_SRC} server.c server_path.c server_fork.c \
server_cmd/server_cmd_pwd.c \
server_cmd/server_cmd_put.c \
server_cmd/server_cmd_bad.c \
server_cmd/server_cmd_ls.c \
server_cmd/server_cmd_mkdir.c \
server_cmd/server_cmd_cd.c \
server_cmd/server_cmd_get.c

CLIENT_SRC = ${COMMON_SRC} client.c client_lexer.c \
client_cmd/client_cmd_pwd.c \
client_cmd/client_cmd_put.c \
client_cmd/client_cmd_bad.c \
client_cmd/client_cmd_ls.c \
client_cmd/client_cmd_mkdir.c \
client_cmd/client_cmd_cd.c \
client_cmd/client_cmd_get.c \
client_cmd/client_cmd_quit.c

SRCDIR = srcs

OBJDIR = objs

LIB = -Llibft/ -lft

INCLUDES = -Ilibft/includes/ -Iincludes/

EXT = libft/libft.a

############################## COLORS ##########################################

BY = "\033[33;1m"
BR = "\033[31;1m"
BG = "\033[32;1m"
BB = "\033[34;1m"
BM = "\033[35;1m"
BC = "\033[36;1m"
Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
M = "\033[35m"
C = "\033[36m"
WT = "\033[37;1m"
W = "\033[0m""\033[32;1m"
WR = "\033[0m""\033[31;5m"
WY = "\033[0m""\033[33;5m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

############################## RULES ###########################################

all: art ${SERVER_NAME} ${CLIENT_NAME}

libft/%:
	@[[ -d libft ]] || (echo ${M}Cloning"   "[libft]...${X} && git clone https://github.com/grumbach/libft &>/dev/null)
	@make -C libft

############################## SERVER ##########################################

SERVER_OBJ = $(addprefix ${OBJDIR}/, $(SERVER_SRC:.c=.o))
CLIENT_DEP = $(addprefix ${OBJDIR}/, $(SERVER_SRC:.c=.d))

${SERVER_NAME}: ${SERVER_OBJ}
	@echo ${B}Compiling [${SERVER_NAME}]...${X}
	@${CC} ${CFLAGS} ${INCLUDES} ${LIB} -o $@ ${SERVER_OBJ}
	@echo ${G}Success"   "[${SERVER_NAME}]${X}

${OBJDIR}/%.o: ${SRCDIR}/%.c ${EXT}
	@echo ${Y}Compiling [$@]...${X}
	@/bin/mkdir -p ${OBJDIR} ${OBJDIR}/client_cmd ${OBJDIR}/server_cmd
	@${CC} ${CFLAGS} ${INCLUDES} -c -o $@ $<
	@printf ${UP}${CUT}

############################## CLIENT ##########################################

CLIENT_OBJ = $(addprefix ${OBJDIR}/, $(CLIENT_SRC:.c=.o))
CLIENT_DEP = $(addprefix ${OBJDIR}/, $(CLIENT_SRC:.c=.d))

${CLIENT_NAME}: ${CLIENT_OBJ}
	@echo ${B}Compiling [${CLIENT_NAME}]...${X}
	@${CC} ${CFLAGS} ${INCLUDES} ${LIB} -o $@ ${CLIENT_OBJ}
	@echo ${G}Success"   "[${CLIENT_NAME}]${X}

${OBJDIR}/%.o: ${SRCDIR}/%.c ${EXT}
	@echo ${Y}Compiling [$@]...${X}
	@/bin/mkdir -p ${OBJDIR} ${OBJDIR}/server_cmd ${OBJDIR}/client_cmd
	@${CC} ${CFLAGS} ${INCLUDES} -c -o $@ $<
	@printf ${UP}${CUT}

############################## GENERAL #########################################

clean:
	@echo ${R}Cleaning"  "[libft objs]...${X}
	@make -C libft/ clean
	@echo ${R}Cleaning"  "[objs]...${X}
	@/bin/rm -Rf ${OBJDIR}

fclean: clean
	@make -C libft/ fclean
	@echo ${R}Cleaning"  "[${SERVER_NAME}]...${X}
	@/bin/rm -f ${SERVER_NAME}
	@/bin/rm -Rf ${SERVER_NAME}.dSYM
	@echo ${R}Cleaning"  "[${CLIENT_NAME}]...${X}
	@/bin/rm -f ${CLIENT_NAME}
	@/bin/rm -Rf ${CLIENT_NAME}.dSYM

test: libft/libft.a
	@${CC} -g ${INCLUDES} -fsanitize=address,undefined ${LIB} \
	-I. -o ${SERVER_NAME} $(addprefix srcs/, ${SERVER_SRC})
	@${CC} -g ${INCLUDES} -fsanitize=address,undefined ${LIB} \
	-I. -o ${CLIENT_NAME} $(addprefix srcs/, ${CLIENT_SRC})

re: fclean all

############################## DECORATION ######################################

art:
	@echo ${BG}
	@echo "            .------.    "
	@echo "           /  ~ ~   \\,------.      ______    "
	@echo "         ,'  ~ ~ ~  /  ("${WR}"@"${X}${BG}")   \\   ,'      \\    "
	@echo "       ,'          /\`.    ~ ~ \\ /         \\    "
	@echo "     ,'           | ,'\\  ~ ~ ~ X     \\  \\  \\    "
	@echo "   ,'  ,'          V--<       (       \\  \\  \\    "
	@echo " ,'  ,'               (vv      \\/\\  \\  \\  |  |    "
	@echo "(__,'  ,'   /         (vv   \"\"    \\  \\  | |  |    "
	@echo "  (__,'    /   /       vv   \"\"\"    \\ |  / / /    "
	@echo "      \\__,'   /  |     vv          / / / / /    "
	@echo "          \\__/   / |  | \\         / /,',','    "
	@echo "             \\__/\\_^  |  \\       /,'',','\\    "
	@echo "                    \`-^.__>.____/  ' ,'   \\    "
	@echo "                            // //---'      |    "
	@echo ${BB} "    ______      ========="${BG}"((((((("${BB}"=================    "
	@echo ${BB} "   / __/ /_____          "${BG}"            | \\ \\  \\    "
	@echo ${BB} "  / /_/ __/ __ \\        "${BG}"             / |  |  \\    "
	@echo ${BB} " / __/ /_/ /_/ /         "${BG}"           / /  / \\  \\    "
	@echo ${BB} "/_/  \\__/ .___/         "${BG}"            \`.     |   \\    "
	@echo ${BB} "       /_/               "${BG}"             \`--------'    "
	@echo ${X}

.PHONY: all clean fclean re art

-include ${CLIENT_DEP}
-include ${SERVER_DEP}
