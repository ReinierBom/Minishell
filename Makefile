# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rbom <rbom@student.codam.nl>                 +#+                      #
#                                                    +#+                       #
#    Created: 2022/11/21 16:58:14 by rbom          #+#    #+#                  #
#    Updated: 2024/10/12 19:47:56 by rbom          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
RLFLAG			=	-lreadline

SRC 			=	0_main/0_0_main.c					\
					0_main/0_1_tester.c					\
					1_init_free/1_1_init.c				\
					1_init_free/1_2_init_free.c			\
					2_env_var/2_1_env_var_sub.c			\
					2_env_var/2_2_env_var_edit.c		\
					3_input/3_1_input.c					\
					4_signal/4_1_signal.c				\
					5_parse/5_0_helper.c				\
					5_parse/5_1_and_or.c				\
					5_parse/5_2_env_1.c					\
					5_parse/5_2_env_2.c					\
					5_parse/5_3_sub.c					\
					5_parse/5_4_pipe.c					\
					5_parse/5_5_cmd.c					\
					5_parse/5_6_arg.c					\
					5_parse/5_7_red.c					\
					5_parse/5_8_red_arg.c				\
					5_parse/5_9_quote.c					\
					6_run/6_1_run_sub.c
			
OBJDIR			=	obj
OBJ				=	$(SRC:%.c=$(OBJDIR)/%.o)
OBJDIRS			=	$(sort $(dir $(OBJ)))



all				:	$(NAME)

$(OBJDIR)/%.o	:	%.c | $(OBJDIRS)
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