# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rbom <rbom@student.codam.nl>                 +#+                      #
#                                                    +#+                       #
#    Created: 2022/11/21 16:58:14 by rbom          #+#    #+#                  #
#    Updated: 2024/08/01 14:37:18 by rbom          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	:=	minishell

CC		:=	cc
CFLAGS	:=	-Wall -Wextra -Werror
RLFLAG	:=	-lreadline

SRC 	:=	minishell_main.c
			
OBJ		:=	${SRC:.c=.o}



all		:	$(NAME)

%.o		:	%.c
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME)	:	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(RLFLAG)
			
clean	:
			rm -rf $(OBJ)

fclean	:	clean
			rm -rf $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re