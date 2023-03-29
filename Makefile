SRC_FILES	=	builtins/builtins.c \
				builtins/builtins2.c \
				builtins/cd.c \
				builtins/cd2.c \
				builtins/echo.c \
				builtins/env.c \
				builtins/exit.c \
				builtins/export.c \
				builtins/heredoc.c \
				builtins/pwd.c \
				builtins/unset.c \
				data.c \
				env1.c \
				env2.c \
				error.c \
				main.c \
				parser/parse.c \
				parser/oldparse.c \
				parser/parseutil.c \
				parser/token.c \
				parser/tokentype.c \
				parser/tokenutil.c \
				parser/tokenvalidation1.c \
				parser/tokenvalidation2.c \
				parser/tokenvalidation3.c \
				parser/buildwrd.c \
				path.c \
				pipeline.c \
				prompt.c \
				redir.c \
				sig.c \
				util/concatstr1.c \
				util/concatstr2.c \
				util/math.c \
				util/mem.c \
				util/str.c \
				util/str2.c \
				util/str3.c \
				util/vector.c \
				wildcard.c \
				wildcard2.c

SRC_DIR		=	src

OBJ_DIR=obj
OBJ_FILES:=$(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.o))

NAME=minishell

CC=gcc
CCFLAGS=-Wall -Wextra -Wpedantic -fno-exceptions -Wpointer-arith -Werror -Isrc
LDFLAGS=-L${HOME}/.brew/opt/readline/lib
LDLIBS=-lreadline

all: $(NAME)

norm:
	norminette src/

noerr: CCFLAGS:=$(subst -Werror,,$(CCFLAGS))
noerr: all

sanit: CCFLAGS+=-g -O0 -fsanitize=address
sanit: LDFLAGS+=-fsanitize=address
sanit: re

debug: CCFLAGS+=-g -O0
debug: re

clean:
	@-rm -rf $(OBJ_DIR)/*.o $(OBJ_DIR)/*.d
	@-rm -rf $(OBJ_DIR)/*/*.o $(OBJ_DIR)/*/*.d

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
