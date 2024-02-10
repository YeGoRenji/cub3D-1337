NAME = cub3D

CFLAGS = -Wall -Wextra -Werror -Ofast #-g #-O3  #-fsanitize=address

LINK_H = -Iinclude

OBJSFOLDER = objs/

OBJS_FILES = main.o \
		     texture.o \
			 drawing.o \
			 vectors_binary.o \
			 utils.o \
			 vectors_unary.o \
			 draw_primitives.o \
			 draw_utils.o \
			 draw_walls.o \
			 draw_minimap.o \
			 draw_bg_fg.o \
			 fps_counter.o \
			 graphics.o \
			 player_input.o

OS := $(shell uname -s)

ifeq ($(OS), Darwin)
	LINKS = -lmlx42 -L"/Users/$(USER)/.brew/opt/glfw/lib/"
else
	LINKS = -lmlx42_linux -ldl -pthread -lm
	CFLAGS += -Wno-unused-result
endif

OBJS = $(foreach obj, $(OBJS_FILES), $(OBJSFOLDER)$(obj))

GLOBAL_HEADERS = include/structs.h

all: objs $(NAME)

objs:
	@mkdir objs

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $@ -L`pwd`/lib $(LINKS) $(LINK_H) -lglfw

$(OBJSFOLDER)%.o: %.c $(GLOBAL_HEADERS)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(LINK_H) -c $< -o $@

$(OBJSFOLDER)%.o: src/drawing/%.c include/drawing.h $(GLOBAL_HEADERS)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(LINK_H) -c $< -o $@

$(OBJSFOLDER)%.o: src/maths/%.c include/maths.h $(GLOBAL_HEADERS)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(LINK_H) -c $< -o $@

$(OBJSFOLDER)%.o: src/input/%.c include/input.h $(GLOBAL_HEADERS)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(LINK_H) -c $< -o $@

re: fclean all

fclean: clean
	rm -rf $(NAME)

clean:
	rm -rf $(OBJS) $(HOT_RELOAD)

.PHONY: all clean fclean re
