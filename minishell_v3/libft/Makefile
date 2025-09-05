# Makefile for mylibft

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

AR = ar rcs

# Libft sources
LIBFT_SRCS = ft_atoi.c \
             ft_bzero.c \
             ft_calloc.c \
             ft_isalnum.c \
             ft_isalpha.c \
             ft_isascii.c \
             ft_isdigit.c \
             ft_isprint.c \
             ft_itoa.c \
             ft_lstadd_back.c \
             ft_lstadd_front.c \
             ft_lstclear.c \
             ft_lstdelone.c \
             ft_lstiter.c \
             ft_lstlast.c \
             ft_lstmap.c \
             ft_lstnew.c \
             ft_lstsize.c \
             ft_memchr.c \
             ft_memcmp.c \
             ft_memcpy.c \
             ft_memmove.c \
             ft_memset.c \
             ft_putchar_fd.c \
             ft_putendl_fd.c \
             ft_putnbr_fd.c \
             ft_putstr_fd.c \
             ft_split.c \
             ft_split_free.c \
             ft_strchr.c \
             ft_strdup.c \
             ft_striteri.c \
             ft_strjoin.c \
             ft_strlcat.c \
             ft_strlcpy.c \
             ft_strlen.c \
             ft_strmapi.c \
             ft_strncmp.c \
             ft_strnstr.c \
             ft_strrchr.c \
             ft_strtrim.c \
             ft_substr.c \
             ft_tolower.c \
             ft_toupper.c

# ft_printf sources
PRINTF_SRCS = ft_printf/ft_printf.c \
              ft_printf/ft_printf_utils1.c \
              ft_printf/ft_printf_utils2.c

# get_next_line sources
GNL_SRCS = get_next_line/get_next_line.c \
           get_next_line/get_next_line_utils.c

SRCS = $(LIBFT_SRCS) $(PRINTF_SRCS) $(GNL_SRCS)

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -I. -Ift_printf -Iget_next_line -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
