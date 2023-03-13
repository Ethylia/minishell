SRC_FILES	=	shell.c \
				env1.c \
				env2.c \

SRC_DIR		=	src

OBJ_DIR=obj
OBJ_FILES:=$(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.o))

NAME=minishell

CC=gcc
CCFLAGS=-Wall -Wextra -Wpedantic -fno-exceptions -Wpointer-arith -Werror
LDFLAGS=-pthread -lreadline

all: mkpaths $(NAME)

norm:
	norminette $(wildcard src/*.c) $(wildcard src/*.h)

noerr: CCFLAGS:=$(subst -Werror,,$(CCFLAGS))
noerr: all

debug: CCFLAGS+=-g -O0
debug: all

clean:
	@-rm -rf $(OBJ_DIR)/*.o $(OBJ_DIR)/*.d
	@-rm -fd $(OBJ_DIR)

fclean: clean
	@-rm -f $(NAME)

mkpaths: $(OBJ_DIR)
$(OBJ_DIR):
	-mkdir $@

re: fclean all

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CCFLAGS) -c -o $@ $< -MMD

$(NAME): $(OBJ_FILES)
	$(CC) $(LDFLAGS) $^ -o $(NAME)

.PHONY: clean fclean re mkpaths all norm
.IGNORE: mkpaths

-include $(OBJ_FILES:.o=.d)