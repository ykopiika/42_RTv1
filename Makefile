# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/13 20:45:29 by ykopiika          #+#    #+#              #
#    Updated: 2019/10/14 19:07:23 by ykopiika         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= RTv1

SRC    :=	check_type_count_nbrs.c\
			figures_normal.c\
			game_loop.c\
			get_next_line2.c\
			instruments.c\
			intersect_figrs.c\
			keyboard.c\
			lighting_calculate.c\
			main.c\
			malloc_lst.c\
			print_error.c\
			ray_tracing.c\
			read_data.c\
			validation_file.c\
			vector_arithmetic_a.c\
			vector_arithmetic_b.c\
			which_figure_closer.c\

#---------- set dir ------------
SRC_PATH := $(CURDIR)/src
OBJ_PATH := $(CURDIR)/obj
OBJ_SRC := $(SRC:.c=.o)
OBJ_SRC := $(addprefix $(OBJ_PATH)/, $(OBJ_SRC))
SRC := $(addprefix $(SRC_PATH)/, $(SRC))

#---------- CC stuff -----------
CC := gcc
FLAG_CC = -Wall -Wextra -Werror

#---------- SDL stuff ----------
SDL_INC =  -I $(CURDIR)/frameworks/SDL2.framework/Headers/ 		\

FLAG_FRM =	-F frameworks

SDL_FLAGS =	-rpath frameworks		\
			-framework SDL2 		\

#---------- libft -----------
LIB_INC =	-I libft/ \
			-I inc/
LIB_FT = libft/libft.a

all: $(NAME)

$(LIB_FT):
	@make -C libft/

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(NAME): $(LIB_FT) $(OBJ_SRC)
	$(CC) $(OBJ_SRC) $(FLAG_FRM) $(SDL_FLAGS) -L libft -lft -o $(NAME)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	$(CC) $(FLAG_CC) $(FLAG_FRM) $(SDL_INC) $(LIB_INC) -c $< -o $@

clean:
	@make -C libft/ clean
	/bin/rm -rf $(OBJ_SRC)
	/bin/rm -rf $(OBJ_PATH)

fclean: clean
	@make -C libft/ fclean
	/bin/rm -rf $(NAME)

re: fclean all

.PHONY: all fclean clean re
