/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   5_5_arg.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 14:37:56 by rbom          #+#    #+#                 */
/*   Updated: 2024/10/02 17:24:13 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* COUNTS ARGUMENTS */
static void	count_arg(t_cmdl *cmdl, t_pipe *pipe)
{
	size_t	i;
	size_t	quote;

	i = len_cmd(pipe);
	quote = check_quote(0, pipe->line[i]);
	while (quote > 0 || (pipe->line[i] != '<' && pipe->line[i] != '>' && pipe->line[i] != '\0'))
	{
		if (quote == 0 && space(pipe->line[i - 1]) == true && space(pipe->line[i]) == false)
			pipe->n_arg++;
		quote = check_quote(quote, pipe->line[i]);
		i++;
	}
	pipe->arg = (char **)malloc(pipe->n_arg * sizeof(char *));
	if (pipe->arg == NULL)
		exit_cmdl(cmdl, 1);
	init_arg(pipe);
}

/* LENGTH ARGUMENT */
static size_t	len_arg(t_cmdl *cmdl, t_pipe *pipe, size_t arg, size_t start)
{
	size_t	len;
	size_t	quote;

	len = 0;
	quote = check_quote(0, pipe->line[start]);
	while (quote > 0 || (space(pipe->line[start + len]) == false && pipe->line[start + len] != '<' && pipe->line[start + len] != '>' && pipe->line[start + len] != '\0'))
	{
		len++;
		quote = check_quote(quote, pipe->line[start + len]);
	}
	pipe->arg[arg] = (char *)malloc(len + 1);
	if (pipe->arg[arg] == NULL)
		exit_cmdl(cmdl, 1);
	return (len);
}

/* COPIES ARGUMENT */
static void	copy_arg(t_pipe *pipe, size_t arg, size_t start, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		pipe->arg[arg][i] = pipe->line[start + i];
		i++;
	}
	pipe->arg[arg][len] = '\0';
}

/* SPLITS ARGUMENTS */
void	split_arg(t_cmdl *cmdl, t_pipe *pipe)
{
	size_t	arg;
	size_t	start;
	size_t	len;

	count_arg(cmdl, pipe);
	arg = 0;
	start = len_cmd(pipe);
	while (arg < pipe->n_arg)
	{
		while (space(pipe->line[start]) == true)
			start++;
		len = len_arg(cmdl, pipe, arg, start);
		copy_arg(pipe, arg, start, len);
		pipe->arg[arg] = split_env_var(cmdl, pipe->arg[arg]);
		pipe->arg[arg] = remove_quote(cmdl, pipe->arg[arg]);
		start += len;
		arg++;
	}
}
