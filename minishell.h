/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 17:10:47 by rbom          #+#    #+#                 */
/*   Updated: 2024/10/04 17:42:51 by rbom          ########   odam.nl         */
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
# include <sys/wait.h>

extern int	g_signal;

typedef struct s_pipe
{
	char	*line;
	char	*cmd;
	size_t	n_arg;
	char	**arg;
	size_t	n_red;
	size_t	*red;
	char	**red_arg;
}	t_pipe;

typedef struct s_cmd
{
	size_t	and_or;
	size_t	open;
	size_t	sub;
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
	pid_t				pid;
	size_t				sub;
	char				*input;
	size_t				n;
	t_cmd				*cmd;
}	t_cmdl;

/* 1_init_free */
/* 1_1_init */
void	init_start(t_cmdl *cmdl, char **envp);
void	init_cmdl(t_cmdl *cmdl);
void	init_cmd(t_cmdl *cmdl);
void	init_pipe(t_cmd *cmd);
void	init_arg(t_pipe *pipe);
/* 1_2_init_free */
void	init_red_arg(t_pipe *pipe);
void	free_cmdl(t_cmdl *cmdl);
void	exit_cmdl(t_cmdl *cmdl, size_t exit_code);

/* 2_env */
/* 2_1_env_substitute */
void	copy_ev(t_cmdl *cmdl, char **envp);
char	*return_ev(t_cmdl *cmdl, char *str);
char	*replace_ev_str(t_cmdl *cmdl, char *str);
/* 2_2_env_edit */
void	add_replace_ev(t_cmdl *cmdl, char *str);
void	remove_ev(t_cmdl *cmdl, char *str);

/* 3_input */
/* 3_1_input */
bool	space(char c);
bool	check_input(t_cmdl *cmdl);

/* 4_signal */
/* 4_1_signal */
void	signal_mode(t_cmdl *cmdl, bool interactive);

/* 5_parse */
/* 5_0_helper */
size_t	check_quote(size_t quote, char c);
char	*remove_space(t_cmdl *cmdl, char *str);
/* 5_1_and_or */
void	parse_cmdl(t_cmdl *cmdl);
/* 5_8_env */
char	*split_env_var(t_cmdl *cmdl, char *str);
/* 5_3_sub */
void	subshell(t_cmdl *cmdl);
/* 5_4_pipe */
void	split_pipe(t_cmdl *cmdl, t_cmd *cmd);
/* 5_5_cmd */
size_t	len_cmd(t_pipe *pipe);
void	copy_cmd(t_cmdl *cmdl, t_pipe *pipe);
/* 5_6_arg */
size_t	check_red(char *str, size_t i);
size_t	start_red(t_pipe *pipe);
void	split_arg(t_cmdl *cmdl, t_pipe *pipe);
/* 5_7_red */
void	copy_red(t_cmdl *cmdl, t_pipe *pipe);
/* 5_8_red_arg */
void	split_red_arg(t_cmdl *cmdl, t_pipe *pipe);
/* 5_9_quote */
char	*concat_str(t_cmdl *cmdl, char **str_arr, size_t n);
char	*remove_quote(t_cmdl *cmdl, char *str);

#endif
