NAME = libftprintf.a

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

HEADER = -I. -I./$(LIBFT_DIR)

SRCS = ft_char.c ft_hex.c ft_int.c ft_printf.c ft_string.c ft_uns.c ft_uns_hex.c \
		ft_uns_maj_hex.c parameters.c ft_percent.c

OBJS = $(SRCS:.c=.o)

CC	= gcc

CFLAGS = -Wall -Werror -Wextra

RM 	= rm -rf

all: $(NAME)

$(NAME):	$(OBJS)
	make -C $(LIBFT_DIR)
	cp $(LIBFT) $(NAME)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

clean:
	$(RM) $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean:	clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)

re:	fclean all

.PHONY: all clean fclean re