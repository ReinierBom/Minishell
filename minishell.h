/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 17:10:47 by rbom          #+#    #+#                 */
/*   Updated: 2024/08/30 20:05:09 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

extern int	g_signal;

typedef struct s_data
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	char				*input_raw;
	// char				**input_split;
}	t_data;

/* minishell_signal.c */
// void	null_sigaction(t_data *data);
void	set_sigaction(t_data *data);

/* minishell_input_line.c */
bool	space(char c);
bool	empty_line(t_data *data);

/* minishell_input_split.c */
// void	split_input(t_data *data);

/* minishell_builtin.c */
bool	ft_strcmp(char *str_1, char *str_2);
void	execute_input(t_data *data);
void	echo_test(t_data *data);

/* minishell_free.c */
void	null_data(t_data *data);
void	free_data(t_data *data);
void	exit_data(t_data *data, size_t exit_code);

#endif
