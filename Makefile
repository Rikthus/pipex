NAME	:=	pipex

CC	:=	gcc
CFLAGS	:=	-Wall -Wextra -Werror

DIR_SRCS	:=	sources
DIR_OBJS	:=	.objs
DIR_INCS	:=	includes

DIR_LIBFT	:=	libft_me

LST_SRCS	:=	pipex.c \
				init_data.c \
				utils.c

LST_OBJS	:=	$(LST_SRCS:.c=.o)
LST_INCS	:=	pipex.h

SRCS	:=	$(addprefix $(DIR_SRCS)/,$(LST_SRCS))
OBJS	:=	$(addprefix $(DIR_OBJS)/,$(LST_OBJS))
INCS	:=	$(addprefix $(DIR_INCS)/,$(LST_INCS))

AR_LIBFT	:=	$(DIR_LIBFT)/libft.a

all	:	$(NAME)

$(NAME)	:	$(OBJS) $(AR_LIBFT)
			$(CC) $(CFLAGS) $^ -o $@

$(DIR_OBJS)/%.o	:	$(DIR_SRCS)/%.c $(INCS) Makefile | $(DIR_OBJS)
					$(CC) $(CFLAGS) -I $(DIR_INCS) -c $< -o $@

$(AR_LIBFT)	:
				$(MAKE) -C $(DIR_LIBFT)

$(DIR_OBJS)	:
				mkdir -p $(DIR_OBJS)

clean	:
			rm -rf $(DIR_OBJS)

fclean	:	clean
			rm -rf $(NAME) infile outfile

re	:	fclean all

.PHONY	:	all clean fclean re
