NAME = cub3D

CFLAGS = -Wall -Wextra -Werror -O3 -Ofast -g #-fsanitize=address #-g

LINK_H = -Iinclude

OBJSFOLDER = objs/

OBJS_FILES = main.o

OBJS = $(foreach obj, $(OBJS_FILES), $(OBJSFOLDER)$(obj))

GLOBAL_HEADERS = include/structs.h

all: objs $(NAME)

objs:
	@mkdir objs

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $@ -L`pwd`/lib -lmlx42 $(LINK_H) -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"

$(OBJSFOLDER)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LINK_H)

# $(OBJSFOLDER)%.o: src/maths/%.c include/maths.h $(GLOBAL_HEADERS)
# 	@echo "Compiling $<..."
# 	@$(CC) $(CFLAGS) $(LINK_H) -c $< -o $@

re: fclean all

fclean: clean
	rm -rf $(NAME)

clean:
	rm -rf $(OBJS)

.PHONY: all clean fclean re
