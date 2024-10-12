/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 17:10:47 by rbom          #+#    #+#                 */
/*   Updated: 2024/10/12 19:56:14 by rbom          ########   odam.nl         */
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

extern int	g_exit;

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
	size_t				sub;
	size_t				sub_cmd;
	char				*input;
	size_t				n;
	t_cmd				*cmd;
}	t_cmdl;

/* TESTS */
void	test_parsing_cmdl(t_cmdl *cmdl);
void	test_parsing_cmd(t_cmd *cmd);
void	test_parsing_pipe(t_cmd *cmd);

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
void	exit_cmdl(t_cmdl *cmdl, size_t exit_code, bool message);

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
/* 5_2_env_1 */
size_t	len_env_var(char *str, size_t start);
size_t	len_non_env_var(char *str, size_t quote, size_t start);
size_t	quote_env_var(char *str, size_t quote, size_t start, size_t len);
char	**count_env_var(t_cmdl *cmdl, char *str);
char	*copy_env_var(t_cmdl *cmdl, char *line, size_t len, size_t start);
/* 5_2_env_2 */
char	*concat_str(t_cmdl *cmdl, char **str_arr, size_t n);
void	split_env_var(t_cmdl *cmdl, t_cmd *cmd);
/* 5_3_sub */
void	subshell(t_cmdl *cmdl);
/* 5_4_pipe */
void	parse_cmd(t_cmdl *cmdl, t_cmd *cmd);
/* 5_5_cmd */
size_t	len_cmd(t_pipe *pipe);
void	copy_cmd(t_cmdl *cmdl, t_pipe *pipe);
/* 5_6_arg */
size_t	check_red(char *str, size_t i);
void	split_arg(t_cmdl *cmdl, t_pipe *pipe);
/* 5_7_red */
void	copy_red(t_cmdl *cmdl, t_pipe *pipe);
/* 5_8_red_arg */
void	split_red_arg(t_cmdl *cmdl, t_pipe *pipe);
/* 5_9_quote */
char	*remove_quote(t_cmdl *cmdl, char *str);

/* 6_run */
/* 6_1_run_sub */
int		comp(char *str_1, char *str_2);
void	run_sub(t_cmdl *cmdl);

#endif
