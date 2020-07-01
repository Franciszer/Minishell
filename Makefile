FLAGS=-Wall -Wextra -Werror
# VARIABLES

NAME= minishell
LIB_DIR= srcs/libft
LIB= ${LIB_DIR}/libft.a
MAIN= srcs/main.c
MAIN_TEST=test/test.c
SRCS=	srcs/parsing/prompt_loop.c\
		srcs/parsing/parsingUtils.c\
		srcs/parsing/tokenLen.c\
		srcs/parsing/tokenize.c\
		srcs/parsing/argv_functions.c\
		srcs/parsing/tokens_syntax_check.c\
		srcs/commands/minishell_exit.c\
		srcs/token_expansion/get_env.c\
		srcs/token_expansion/expand_tokens.c\
		srcs/token_expansion/token_expansion_utils.c\
		srcs/launch_commands/command_functions.c\
		srcs/launch_commands/minishell_launch.c\
		srcs/utils/print_tokens.c
INCLUDE_DIRS = -I srcs/libft\
			-I includes	
OBJECTS = ${SRCS:.c=.o}

# COLORS

GREEN=\033[0;32m
LIGHT_BLUE=\033[0;34m
YELLOW=\033[0;33m
NC=\033[0m

all: $(NAME)

.c.o:
	@${CC} ${FLAGS} ${INCLUDE_DIRS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJECTS}
			@rm -rf logs
			@mkdir logs
			@echo "${LIGHT_BLUE}Compiling minishell...${NC}"
			@make -C ${LIB_DIR} > /dev/null 2>&1
			@cc ${FLAGS} -fsanitize=address ${MAIN} ${OBJECTS} ${INCLUDE_DIRS} ${LIB} -o ${NAME}
			@echo "${GREEN}✓  minishell successfully compiled${NC}"
start: all
	@./${NAME}
	@rm -rf ${NAME}

valgrind_start: all
	@valgrind --leak-check=full --show-leak-kinds=all ./${NAME}

test: all
	@cc -fsanitize=address ${MAIN_TEST} ${OBJECTS} ${INCLUDE_DIRS} ${LIB} -o test_exec
	@./test_exec
	@rm -rf test_exec

clean:
		@rm -rf logs
		@echo "${LIGHT_BLUE}Cleaning minishell...${NC}"
		@make clean -C ${LIB_DIR} > /dev/null 2>&1
		@rm -rf ${OBJECTS}
		@echo "${GREEN}✓  minishell successfully cleaned${NC}"

fclean: clean
		@rm -rf ${LIB}
		@echo "${GREEN}✓  lib succsessfully deleted${NC}"
		@rm -rf $(NAME)
		@echo "${GREEN}✓  minishell executable successfully deleted${NC}"

re: fclean all

.PHONY: all start clean fclean re ${NAME}