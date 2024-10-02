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
	char		*line;
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
	size_t	open;
	size_t	priority;
	size_t	close;
	char	*line;
	size_t	n;
	t_pipe	*pipe;
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

/* minishell_env_substitute.c */
void	copy_ev(t_cmdl *cmdl, char **envp);
char	*return_ev(t_cmdl *cmdl, char *str);
char	*replace_ev_str(t_cmdl *cmdl, char *str);

/* minishell_env_edit.c */
void	add_replace_ev(t_cmdl *cmdl, char *str);
void	remove_ev(t_cmdl *cmdl, char *str);

/* minishell_init_free.c */
void	init_cmdl(t_cmdl *cmdl);
void	init_cmd(t_cmdl *cmdl);
void	init_pipe(t_cmd *cmd);
void	init_arg(t_pipe *pipe);
void	init_red_arg(t_pipe *pipe);
void	free_cmdl(t_cmdl *cmdl);
void	exit_cmdl(t_cmdl *cmdl, size_t exit_code);

/* minishell_input.c */
bool	space(char c);
bool	empty_line(t_cmdl *cmdl);

/* minishell_signal.c */
// void	signal_mode(t_cmdl *cmdl, bool interactive);

/* minishell_split_helper.c */
size_t	check_quote(size_t quote, char c);
char	*remove_space(t_cmdl *cmdl, char *str);

/* minishell_split_and_or.c */
void	split_and_or(t_cmdl *cmdl);

/* minishell_split_priority.c */
void	prioritise(t_cmdl *cmdl);

void	split_pipe(t_cmdl *cmdl, t_cmd *cmd);

size_t	len_cmd(t_pipe *p);
void	copy_cmd(t_cmdl *cmdl, t_pipe *p);

void	split_arg(t_cmdl *cmdl, t_pipe *p);

size_t	check_red(char *str, size_t i);
size_t	start_red(t_pipe *pipe);
void	copy_red(t_cmdl *cmdl, t_pipe *pipe);

void	split_red_arg(t_cmdl *cmdl, t_pipe *pipe);

char	**count_env_var(t_cmdl *cmdl, char *str);
char	*split_env_var(t_cmdl *cmdl, char *str);
char	*concat_str(t_cmdl *cmdl, char **str_arr, size_t n);
char	*remove_quote(t_cmdl *cmdl, char *str);



#endif
