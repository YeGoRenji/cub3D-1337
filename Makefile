# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 17:13:54 by ylyoussf          #+#    #+#              #
#    Updated: 2024/02/14 18:21:14 by ylyoussf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CFLAGS = -Wall -Wextra -Werror   -g -Ofast#-fsanitize=address

LINK_H = -Iinclude

OBJSFOLDER = objs/

OBJS_FILES = main.o \
		     texture.o \
			 utils.o \
			 vectors_binary.o \
			 vectors_unary.o \
			 draw_primitives.o \
			 draw_utils.o \
			 draw_walls.o \
			 draw_minimap.o \
			 draw_bg_fg.o \
			 graphics.o \
			 fps_counter.o \
			 error.o \
			 init.o \
			 player_input.o \
			 event_hooks.o \
			 raycasting.o \
			 raycasting_utils.o \
			 multithreading.o    \
			 parse.o		 	  \
			 parse_utils.o	  	   \
			 map_validation.o		\
			 validation_utils.o		 \
			 player_utils.o			  \
			 line_utils.o			   \
			 p_map_utils.o				\
			 map_ds_utils.o				 \
			 texture_utils.o			  \
			 parse_not_utils.o			   \
			 parse_definitely_not_utils.o   \
			 tiny_parsing_helpers.o			 \
		     clean_map.o					  \
		     clean_mlx.o					   \
		     clean_textures.o

OS := $(shell uname -s)

ifeq ($(OS), Darwin)
	LINKS = -lmlx42 -L"/Users/$(USER)/.brew/opt/glfw/lib/"
else
	LINKS = -lmlx42_linux -ldl -pthread -lm
	CFLAGS += -Wno-unused-result
endif

OBJS = $(foreach obj, $(OBJS_FILES), $(OBJSFOLDER)$(obj))

GLOBAL_HEADERS = include/structs.h

LIBFT = src/libft/libft.a

all: objs $(NAME)

objs:
	@mkdir objs

$(LIBFT):
	@echo "Compiling libft..."
	@make -C src/libft bonus

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(CFLAGS) $(LIBFT) -o $@ -L`pwd`/lib $(LINKS) $(LINK_H) -lglfw

$(OBJSFOLDER)%.o: %.c $(GLOBAL_HEADERS)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(LINK_H) -c $< -o $@

$(OBJSFOLDER)%.o: src/drawing/%.c include/drawing.h $(GLOBAL_HEADERS)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(LINK_H) -c $< -o $@

$(OBJSFOLDER)%.o: src/maths/%.c include/maths.h $(GLOBAL_HEADERS)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(LINK_H) -c $< -o $@

$(OBJSFOLDER)%.o: src/hooks/%.c include/hooks.h $(GLOBAL_HEADERS)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(LINK_H) -c $< -o $@

$(OBJSFOLDER)%.o: src/raycasting/%.c include/raycasting.h $(GLOBAL_HEADERS)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(LINK_H) -c $< -o $@

$(OBJSFOLDER)%.o: src/parsing/%.c include/parse.h $(GLOBAL_HEADERS)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(LINK_H) -c $< -o $@

$(OBJSFOLDER)%.o: src/validation/%.c include/validation.h $(GLOBAL_HEADERS)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(LINK_H) -c $< -o $@

$(OBJSFOLDER)%.o: src/cleaning/%.c include/clean.h $(GLOBAL_HEADERS)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(LINK_H) -c $< -o $@

re: fclean all

fclean: clean
	rm -rf $(NAME)
	make -C src/libft clean

clean:
	rm -rf $(OBJS)
	make -C src/libft fclean

.PHONY: all clean fclean re
