/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 17:10:47 by rbom          #+#    #+#                 */
/*   Updated: 2024/09/08 14:55:27 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

extern int	g_signal;

typedef struct s_cmd
{
	size_t	and_or;
	size_t	exit_status;
	char	*raw;
}	t_cmd;

typedef struct s_cmdl
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	char				**env;
	char				*input;
	size_t				n;
	t_cmd				*cmd;
}	t_cmdl;

/* minishell_signal.c */
// void	null_sigaction(t_data *data);
void	handle_sigint_ia(int sig);
void	handle_sigint_nia(int sig);
void	handle_sigquit_ia(int sig);
void	handle_sigquit_nia(int sig);
// void	sa_ia_mode(t_data *data);
// void	sa_nia_mode(t_data *data);

/* minishell_input.c */
bool	space(char c);
// bool	empty_line(t_data *data);

/* minishell_input_split.c */
// void	split_input(t_data *data);

/* minishell_builtin.c */
bool	ft_strcmp(char *str_1, char *str_2);
// void	execute_input(t_data *data);
// void	echo_test(t_data *data);

/* minishell_free.c */
void	init_cmdl(t_cmdl *cmdl, char **envp);

#endif
