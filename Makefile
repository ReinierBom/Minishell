# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rbom <rbom@student.codam.nl>                 +#+                      #
#                                                    +#+                       #
#    Created: 2022/11/21 16:58:14 by rbom          #+#    #+#                  #
#    Updated: 2024/08/02 18:20:58 by rbom          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
RLFLAG			=	-lreadline

SRC 			=	minishell_main.c		\
					minishell_input_line.c	\
					minishell_input_split.c	\
					minishell_builtin.c
			
OBJ				=	$(SRC:%.c=$(OBJDIR)/%.o)
OBJDIR			=	obj



all				:	$(NAME)

$(OBJDIR)		:
					mkdir -p $(OBJDIR)

$(OBJDIR)/%.o	:	%.c
					$(CC) $(CFLAGS) -c $< -o $@

$(NAME)			:	$(OBJDIR) $(OBJ)
					$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(RLFLAG)
			
clean			:
					rm -rf $(OBJDIR)

fclean			:	clean
					rm -rf $(NAME)

re				:	fclean all

.PHONY			:	all clean fclean re