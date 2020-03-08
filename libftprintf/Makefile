# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dpattij <dpattij@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2019/11/07 01:15:55 by dpattij        #+#    #+#                 #
#    Updated: 2020/02/20 19:33:29 by dpattij          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ftprintf
NAME := $(NAME:%=lib%.a)

FLAGS_RELEASE = -Wall -Wextra -Werror -O3 -D IS_BONUS

INCLUDE_DIR = ./include/
FT_DIR = ./libft/
FT_INCLUDE_DIR = $(FT_DIR)
FT_ARCHIVE = $(FT_DIR)/libft.a
OBJ_DIR = ./obj/
BONUS_DIR = ./bonus/

SRC_DIR = ./src/

SRC_FILES =	ft_printf \
			handler_percent \
			handler_char \
			handler_string \
			handler_pointer \
			handler_int \
			handler_uint \
			handler_uint_hex \
			handler_uint_hex_upper \
			putnbr_base \
			number_length \
			flag_zeropadding \
			flag_leftjustify \
			flag_passedwidth \
			flag_formatwidth \
			flag_doprecision \
			math \
			putchr
SRC_FILES := $(SRC_FILES:%=%.o)
SRC_OBJECTS = $(SRC_FILES:%=%)

BONUS_FILES =	flag_always_sign \
				flag_spaced_sign \
				flag_alternative \
				flag_groupedby1k
BONUS_FILES := $(BONUS_FILES:%=%_bonus.o)
BONUS_OBJECTS := $(BONUS_FILES:%=%)
BONUS_FLAGS = -D IS_BONUS

all: $(NAME)

$(NAME): $(SRC_FILES:%=$(OBJ_DIR)%)
	@ar	rcs	$(NAME) \
			$(SRC_OBJECTS:%=$(OBJ_DIR)%)
	@echo BUILD $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC)	-I $(INCLUDE_DIR) \
			-I $(FT_INCLUDE_DIR) \
			-c $^ \
			-o $@ \
			$(FLAGS_RELEASE)
	@echo CC $^

$(BONUS_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(BONUS_DIR)
	@$(CC)	-I $(INCLUDE_DIR) \
			-I $(FT_INCLUDE_DIR) \
			-c $^ \
			-o $@ \
			$(FLAGS_RELEASE) \
			$(BONUS_FLAGS)
	@echo CC $^

bonus: $(SRC_FILES:%=$(BONUS_DIR)%) $(BONUS_FILES:%=$(BONUS_DIR)%)
	@ar	rcs	$(NAME) \
			$(SRC_OBJECTS:%=$(BONUS_DIR)%) \
			$(BONUS_OBJECTS:%=$(BONUS_DIR)%)
	@echo BUILD $(NAME) BONUS

clean:
	@rm -rf	$(SRC_OBJECTS) $(BONUS_OBJECTS) $(OBJ_DIR) $(BONUS_DIR)

fclean: clean
	@rm -rf	$(NAME)

re: fclean
	@$(MAKE)
