# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rbom <rbom@student.codam.nl>                 +#+                      #
#                                                    +#+                       #
#    Created: 2022/11/21 16:58:14 by rbom          #+#    #+#                  #
#    Updated: 2024/09/13 16:34:56 by rbom          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
RLFLAG			=	-lreadline

SRC 			=	minishell_main.c			\
					minishell_env_substitute.c	\
					minishell_env_edit.c		\
					minishell_input.c			\
					minishell_init_free.c		\
					minishell_signal.c			\
					minishell_split_helper.c	\
					minishell_split_and_or.c	\
					minishell_split_priority.c	\
					minishell_split_pipe.c		\
					minishell_split_cmd.c		\
					minishell_split_arg.c		\
					minishell_split_red.c		\
					minishell_split_red_arg.c	\
					minishell_count_env.c		\
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