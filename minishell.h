/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 17:10:47 by rbom          #+#    #+#                 */
/*   Updated: 2024/09/13 18:54:26 by rbom          ########   odam.nl         */
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

typedef struct s_pipe
{
	char		*raw;
	char		*cmd;
	size_t		n_arg;
	char		**arg;
	size_t		n_red;
	size_t		*red;
	char		**red_arg;
}	t_pipe;

typedef struct s_cmd
{
	size_t	and_or;
	char	*raw;
	size_t	n;
	t_pipe	*p;
}	t_cmd;

typedef struct s_cmdl
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	char				**env;
	char				*input;
	char				*no_par;
	size_t				n;
	t_cmd				*cmd;
}	t_cmdl;

bool	space(char c);
bool	empty_line(t_cmdl *cmdl);

size_t	check_quote(size_t quote, char c);
size_t	count_par(t_cmdl *cmdl);
void	remove_par(t_cmdl *cmdl);

size_t	check_and_or(char *str, size_t i);
void	count_and_or(t_cmdl *cmdl);
size_t	len_and_or(t_cmdl *cmdl, size_t cmd, size_t start);
void	copy_and_or(t_cmdl *cmdl, size_t cmd, size_t start);
void	split_and_or(t_cmdl *cmdl);

void	count_pipe(t_cmdl *cmdl);
size_t	len_pipe(t_cmdl *cmdl, size_t cmd, size_t p, size_t start);
void	copy_pipe(t_cmdl *cmdl, size_t cmd, size_t p, size_t start);
void	split_pipe(t_cmdl *cmdl);

void	len_cmd(t_cmdl *cmdl);
void	copy_cmd(t_cmdl *cmdl);
void	count_arg(t_cmdl *cmdl);

void	copy_ev(t_cmdl *cmdl, char **envp);
char	*return_ev(t_cmdl *cmdl, char *str);
void	replace_ev_str(t_cmdl *cmdl, char *str);
void	replace_ev_arr(t_cmdl *cmdl, char **arr, size_t n);

void	add_ev(t_cmdl *cmdl, char *str);
bool	check_ev(t_cmdl *cmdl, char *str, size_t i);
void	replace_ev(t_cmdl *cmdl, char *str);
void	add_replace_ev(t_cmdl *cmdl, char *str);
void	remove_ev(t_cmdl *cmdl, char *str);

void	init_cmdl(t_cmdl *cmdl);
void	free_cmdl(t_cmdl *cmdl);
void	exit_cmdl(t_cmdl *cmdl, size_t exit_code);

#endif
