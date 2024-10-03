# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rbom <rbom@student.codam.nl>                 +#+                      #
#                                                    +#+                       #
#    Created: 2022/11/21 16:58:14 by rbom          #+#    #+#                  #
#    Updated: 2024/10/02 17:59:27 by rbom          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
RLFLAG			=	-lreadline

SRC 			=	0_main/0_main.c				\
					1_init_free/1_1_init.c		\
					1_init_free/1_2_init_free.c	\
					2_env/2_1_env_substitute.c	\
					2_env/2_2_env_edit.c		\
					3_input/3_1_input.c			\
					4_signal/4_1_signal.c		\
					5_parse/5_0_helper.c		\
					5_parse/5_1_and_or.c		\
					5_parse/5_2_sub.c			\
					5_parse/5_3_pipe.c			\
					5_parse/5_4_cmd.c			\
					5_parse/5_5_arg.c			\
					5_parse/5_6_red.c			\
					5_parse/5_7_red_arg.c		\
					5_parse/5_8_env.c			\
					5_parse/5_9_quote.c
			
OBJDIR			=	obj
OBJ				=	$(SRC:%.c=$(OBJDIR)/%.o)
OBJDIRS			=	$(sort $(dir $(OBJ)))



all				:	$(NAME)

$(OBJDIR)/%.o	: %.c | $(OBJDIRS)
					$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIRS)		:
					mkdir -p $(OBJDIRS)

$(NAME)			:	$(OBJ)
					$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(RLFLAG)
			
clean			:
					rm -rf $(OBJDIR)

fclean			:	clean
					rm -f $(NAME)

re				:	fclean all

.PHONY			:	all clean fclean re