SRCS	=	ft_printf.c ft_putchar.c ft_putnbr.c ft_putstr.c ft_uputnbr.c ft_putnbr_hex.c ft_putnbr_hexxx.c ft_putaddr.c

CC		=	gcc

FLAGS	=	-Wall -Wextra -Werror

OBJS	=	${SRCS:.c=.o}

NAME	=	libftprintf.a

RM		=	rm -f

$(NAME):	$(OBJS)
			@ar rcs $(NAME) $(OBJS)

all:		$(NAME)

clean:	
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all