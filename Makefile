# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By:                                              +#+                      #
#                                                    +#+                       #
#    Created: Invalid date        by                #+#    #+#                 #
#    Updated: 2020/03/13 12:37:44 by tuperera      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

###########################

NAME			=	minishell

FLAGS			=	-Wall -Wextra -Werror -pedantic -std=c89
FLAGS_DEBUG		=	-Wall -Wextra -g
FLAGS_RDBG		=	-Wall -Wextra -Werror -pedantic -std=c89 -g
FLAGS_BIN		=
FLAGS_BIN_ASAN	=	-fsanitize=address

INCLUDE_DIRS	=	./include/ ./libft/ ./libftprintf/include/
SRC_DIR			=	./src/
OBJ_DIR			=	./obj/
SRC_SUBDIRS		=	runtime_loop std parser vector vm table builtins

LIBFT_DIR		=	./libft/
LIBFTPRINTF_DIR =	./libftprintf/

SRC_FILES		=	main \
					builtins/builtin_cd \
					builtins/builtin_echo \
					builtins/builtin_env \
					builtins/builtin_exit \
					builtins/builtin_export \
					builtins/builtin_manage \
					builtins/builtin_pwd \
					builtins/builtin_unset \
					parser/cb_command \
					parser/cb_item \
					parser/cb_line \
					parser/cb_operation \
					parser/expand_line \
					parser/is_control \
					parser/is_escapable \
					parser/is_literal_space \
					parser/is_string_quote \
					parser/preprocess_line \
					parser/separate_commands \
					parser/skip_atleast \
					parser/take_char \
					parser/take_number \
					parser/take_while \
					runtime_loop/display_prompt \
					runtime_loop/read_char \
					runtime_loop/read_line \
					runtime_loop/take_input \
					runtime_loop/runtime_loop \
					runtime_loop/evaluate_input \
					std/ft_realloc \
					std/ft_perror \
					table/table_destroy \
					table/table_get \
					table/table_insert \
					table/table_new \
					table/table_remove \
					vector/vector_destroy \
					vector/vector_get \
					vector/vector_getr \
					vector/vector_new \
					vector/vector_new_dtor \
					vector/vector_push \
					vector/vector_pop \
					vector/vector_foreach \
					vector/vector_resize \
					vector/vector_with_capacity \
					vector/vector_with_capacity_dtor \
					vm/handle_op_append \
					vm/handle_op_call \
					vm/handle_op_command \
					vm/handle_op_pipe \
					vm/handle_op_read \
					vm/handle_op_write \
					vm/run_process \
					vm/vm_execute  \
					vm/switch_to_process

###########################

INCLUDE_DIRS := $(INCLUDE_DIRS:%=-I%)
SRC_FILES := $(SRC_FILES:%=%.o)
OBJ_FILES := $(SRC_FILES:%=$(OBJ_DIR)%)
OBJ_SUBDIRS := $(SRC_SUBDIRS:%=$(OBJ_DIR)%)

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@$(MAKE) libft
	@$(MAKE) libftprintf
	@echo BUILD $(NAME)
	@$(CC)	$^ \
			-o $(NAME) \
			-L $(LIBFT_DIR) -lft \
			-L $(LIBFTPRINTF_DIR) -lftprintf \
			$(FLAGS) \
			$(FLAGS_BIN)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p	$(OBJ_DIR) \
				$(OBJ_SUBDIRS)
	@$(CC)	$(INCLUDE_DIRS) \
			-c $^ \
			-o $@ \
			$(FLAGS)
	@echo CC $^

re: fclean
	@$(MAKE)

clean:
	@$(MAKE) libftclean
	@$(MAKE) libftprintfclean
	@$(RM) -rf $(OBJ_DIR)
	@echo CLEAN $(OBJ_DIR)

fclean: clean
	@$(MAKE) libftfclean
	@$(MAKE) libftprintffclean
	@$(RM) -f $(NAME)
	@echo FCLEAN $(NAME)

debug: FLAGS = $(FLAGS_DEBUG)
debug: all
asan: FLAGS_BIN = $(FLAGS_BIN_ASAN)
asan: rdb

rdebug: fclean
	@$(MAKE) debug

srdb: FLAGS = $(FLAGS_RDBG)
srdb: all
rdb: fclean
	@$(MAKE) srdb

rafl: export CC = ~/afl/afl-clang
rafl: rasan

rasan: fclean
	@$(MAKE) asan

libft:
	@$(MAKE) -C $(LIBFT_DIR)
	@echo BUILD libft

libftclean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	@echo CLEAN libft

libftre:
	@$(MAKE) re -C $(LIBFT_DIR)
	@echo RE libft

libftfclean:
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@echo FCLEAN libft

libftprintf:
	@$(MAKE) bonus -C $(LIBFTPRINTF_DIR)
	@echo BUILD libftprintf

libftprintfclean:
	@$(MAKE) clean -C $(LIBFTPRINTF_DIR)
	@echo CLEAN libftprintf

libftprintfre:
	@$(MAKE) re -C $(LIBFTPRINTF_DIR)
	@echo RE libftprintf

libftprintffclean:
	@$(MAKE) fclean -C $(LIBFTPRINTF_DIR)
	@echo FCLEAN libftprintf

.PHONY:	all re clean fclean libft libftprintf \
		libftclean libftre libftfclean libftprintfclean \
		libftprintfre libftprintffclean
