SRC_FILES	=	$(wildcard *.c) $(wildcard */*.c)

SRC_DIR		=	.

OBJ_DIR=obj
OBJ_FILES:=$(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.o))

NAME=minishell

CC=gcc
CCFLAGS=-Wall -Wextra -Wpedantic -fno-exceptions -Wpointer-arith -Werror -Isrc
LDFLAGS=
LDLIBS=-pthread -lreadline

all: $(NAME)

norm:
	norminette src/

noerr: CCFLAGS:=$(subst -Werror,,$(CCFLAGS))
noerr: all

debug: CCFLAGS+=-g -O0
debug: all

clean:
	@-rm -rf $(OBJ_DIR)/*.o $(OBJ_DIR)/*.d
	@-rm -fd $(OBJ_DIR)

fclean: clean
	@-rm -f $(NAME)

re: fclean all

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) -c -o $@ $< -MMD

$(NAME): $(OBJ_FILES)
	$(CC) $^ -o $(NAME) $(LDFLAGS) $(LDLIBS) 

.PHONY: clean fclean re all norm

-include $(OBJ_FILES:.o=.d)
