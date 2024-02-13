CC = cc

NAME = libft.a

CFLAGS = -Wall -Wextra -Werror -I ../../include #-g -fsanitize=address

SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
		 ft_isprint.c ft_isascii.c ft_itoa.c ft_tolower.c ft_toupper.c \
		 ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
		 ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		 ft_split.c ft_strtrim.c ft_substr.c ft_strmapi.c ft_striteri.c \
		 ft_strchr.c ft_strrchr.c ft_strdup.c ft_strjoin.c ft_strlen.c \
		 ft_strnstr.c ft_strncmp.c ft_strlcpy.c ft_strlcat.c get_next_line.c \
		 get_next_line_utils.c

OBJ = $(SRC:.c=.o)

bonus_src = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
		   ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
		   ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

bonus_obj = $(bonus_src:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ) ../../include/libft.h
	@echo "[LIBFT] Creating $(NAME)..."
	@ar rcs $@ $(OBJ)

bonus : $(OBJ) $(bonus_obj) ../../include/libft.h
	@echo "[LIBFT] Creating $(NAME)..."
	@ar rcs $(NAME) $^

%.o : %.c ../../include/libft.h
	@echo "[LIBFT] Compiling $<..."
	@$(CC) $(CFLAGS)  -c $< -o $@

clean :
	rm -rf $(OBJ) $(bonus_obj)
fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY: clean fclean re bonus
