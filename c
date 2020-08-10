FLAGS=-Wall -Wextra  -Werror#-fsanitize=address
# -static-libasan -fPIE -pie
# VARIABLES

NAME= minishell
LIB_DIR= srcs/libft
LIB= ${LIB_DIR}/libft.a
MAIN= srcs/main.c
MAIN_TEST=test/test.c
SRCS=	srcs/parsing/prompt_loop.c\
		srcs/parsing/parsing_utils.c\
		srcs/parsing/token_len.c\
		srcs/parsing/tokenize.c\
		srcs/parsing/syntax_check.c\
		srcs/commands/search_path.c\
		srcs/token_expansion/get_env.c\
		srcs/token_expansion/expand_tokens.c\
		srcs/token_expansion/expand_tokens_utils.c\
		srcs/token_expansion/token_expansion_utils.c\
		srcs/launch_commands/minishell_launch.c\
		srcs/launch_commands/minishell_launch_utils.c\
		srcs/launch_commands/minishell_launch_utils2.c\
		srcs/launch_commands/execute_commands.c\
		srcs/launch_commands/command_utils.c\
		srcs/builtins/builtin_cd.c\
		srcs/builtins/builtin_cd2.c\
		srcs/builtins/builtin_exit.c\
		srcs/builtins/builtin_pwd.c\
		srcs/builtins/builtin_env.c\
		srcs/builtins/builtin_echo.c\
		srcs/builtins/builtin_export.c\
		srcs/builtins/builtin_export2.c\
		srcs/builtins/builtin_export3.c\
		srcs/builtins/builtin_unset.c\
		srcs/builtins/launch_builtin.c\
		srcs/signals/signal_handlers.c\
		srcs/utils/print_tokens.c\
		srcs/pipe/execute_pipes.c\
		srcs/redirections/redirections_utils.c\
		srcs/redirections/redirections_utils2.c

INCLUDE_DIRS = -I srcs/libft\
			-I includes	
OBJECTS = ${SRCS:.c=.o}

# COLORS

GREEN=\033[0;32m
LIGHT_BLUE=\033[0;34m
RED=\033[0;31m
YELLOW=\033[0;33m
NC=\033[0m

all: $(NAME)

.c.o:
	@printf "${LIGHT_BLUE}=>	"
	${CC} ${FLAGS} ${INCLUDE_DIRS} -c $< -o ${<:.c=.o}
	@printf "${NC}"

$(NAME):	${OBJECTS}
	@rm -rf logs
	@mkdir logs
	@make -C ${LIB_DIR}
	@printf "${YELLOW}=>	"
	cc ${FLAGS} ${MAIN} ${OBJECTS} ${INCLUDE_DIRS} ${LIB} -o ${NAME}
	@echo "${GREEN}✓	${NAME} compiled${NC}"

start: all
	@@echo "${GREEN}✓  minishell launched${NC}"
	@./${NAME}
	@rm -rf ${NAME}

valgrind_start: all
	@valgrind --leak-check=full --show-leak-kinds=definite ./${NAME}

test: all
	@cc ${MAIN_TEST} ${OBJECTS} ${INCLUDE_DIRS} ${LIB} -o test_exec
	@./test_exec

clean:
	@rm -rf logs
	@printf "${RED}X	"
	rm -rf ${OBJECTS}
	@printf "${NC}"
	make -C srcs/libft clean
	@echo "${GREEN}✓	${NAME} clean${NC}"
	@rm -rf test_exec

fclean: clean
	@rm -rf ${LIB}
	@echo "${GREEN}✓	lib successfully deleted${NC}"
	@rm -rf $(NAME)
	@echo "${GREEN}✓	${NAME} executable successfully deleted${NC}"

re: fclean all

.PHONY: all start clean fclean re ${NAME}
FLAGS=-Wall -Wextra  -Werror#-fsanitize=address
# -static-libasan -fPIE -pie
# VARIABLES

NAME= minishell
LIB_DIR= srcs/libft
LIB= ${LIB_DIR}/libft.a
MAIN= srcs/main.c
MAIN_TEST=test/test.c
SRCS=	srcs/parsing/prompt_loop.c\
		srcs/parsing/parsing_utils.c\
		srcs/parsing/token_len.c\
		srcs/parsing/tokenize.c\
		srcs/parsing/syntax_check.c\
		srcs/commands/search_path.c\
		srcs/token_expansion/get_env.c\
		srcs/token_expansion/expand_tokens.c\
		srcs/token_expansion/expand_tokens_utils.c\
		srcs/token_expansion/token_expansion_utils.c\
		srcs/launch_commands/minishell_launch.c\
		srcs/launch_commands/minishell_launch_utils.c\
		srcs/launch_commands/minishell_launch_utils2.c\
		srcs/launch_commands/execute_commands.c\
		srcs/launch_commands/command_utils.c\
		srcs/builtins/builtin_cd.c\
		srcs/builtins/builtin_cd2.c\
		srcs/builtins/builtin_exit.c\
		srcs/builtins/builtin_pwd.c\
		srcs/builtins/builtin_env.c\
		srcs/builtins/builtin_echo.c\
		srcs/builtins/builtin_export.c\
		srcs/builtins/builtin_export2.c\
		srcs/builtins/builtin_export3.c\
		srcs/builtins/builtin_unset.c\
		srcs/builtins/launch_builtin.c\
		srcs/signals/signal_handlers.c\
		srcs/utils/print_tokens.c\
		srcs/pipe/execute_pipes.c\
		srcs/redirections/redirections_utils.c\
		srcs/redirections/redirections_utils2.c

INCLUDE_DIRS = -I srcs/libft\
			-I includes	
OBJECTS = ${SRCS:.c=.o}

# COLORS

GREEN=\033[0;32m
LIGHT_BLUE=\033[0;34m
RED=\033[0;31m
YELLOW=\033[0;33m
NC=\033[0m

all: $(NAME)

.c.o:
	@printf "${LIGHT_BLUE}=>	"
	${CC} ${FLAGS} ${INCLUDE_DIRS} -c $< -o ${<:.c=.o}
	@printf "${NC}"

$(NAME):	${OBJECTS}
	@rm -rf logs
	@mkdir logs
	@make -C ${LIB_DIR}
	@printf "${YELLOW}=>	"
	cc ${FLAGS} ${MAIN} ${OBJECTS} ${INCLUDE_DIRS} ${LIB} -o ${NAME}
	@echo "${GREEN}✓	${NAME} compiled${NC}"

start: all
	@@echo "${GREEN}✓  minishell launched${NC}"
	@./${NAME}
	@rm -rf ${NAME}

valgrind_start: all
	@valgrind --leak-check=full --show-leak-kinds=definite ./${NAME}

test: all
	@cc ${MAIN_TEST} ${OBJECTS} ${INCLUDE_DIRS} ${LIB} -o test_exec
	@./test_exec

clean:
	@rm -rf logs
	@printf "${RED}X	"
	rm -rf ${OBJECTS}
	@printf "${NC}"
	make -C srcs/libft clean
	@echo "${GREEN}✓	${NAME} clean${NC}"
	@rm -rf test_exec

fclean: clean
	@rm -rf ${LIB}
	@echo "${GREEN}✓	lib successfully deleted${NC}"
	@rm -rf $(NAME)
	@echo "${GREEN}✓	${NAME} executable successfully deleted${NC}"

re: fclean all

.PHONY: all start clean fclean re ${NAME}
