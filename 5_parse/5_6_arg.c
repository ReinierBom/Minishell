/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   5_6_arg.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 14:37:56 by rbom          #+#    #+#                 */
/*   Updated: 2024/10/12 20:52:30 by rbom          ########   odam.nl         */
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
	while (quote > 0 || pipe->line[i] != '\0')
	{
		if (quote == 0 && (pipe->line[i] == '<' || pipe->line[i] == '>'))
		{
			while (space(pipe->line[i]) == true
				|| pipe->line[i] == '<' || pipe->line[i] == '>')
				i++;
			while (quote > 0 || (pipe->line[i] != '<' && pipe->line[i] != '>'
					&& pipe->line[i] != '\0' && space(pipe->line[i]) == false))
				quote = check_quote(quote, pipe->line[i++]);
		}
		else if (!quote && space(pipe->line[i - 1]) && !space(pipe->line[i]))
			pipe->n_arg++;
		quote = check_quote(quote, pipe->line[i++]);
	}
	pipe->arg = (char **)malloc(pipe->n_arg * sizeof(char *));
	if (pipe->arg == NULL)
		exit_cmdl(cmdl, 1, false);
	init_arg(pipe);
}

/* LENGTH ARGUMENT */
static size_t	len_arg(t_cmdl *cmdl, t_pipe *pipe, size_t arg, size_t start)
{
	size_t	len;
	size_t	quote;

	len = start;
	quote = check_quote(0, pipe->line[len]);
	while (quote > 0 || (pipe->line[len] != '<' && pipe->line[len] != '>'
			&& pipe->line[len] != '\0' && space(pipe->line[len]) == false))
	{
		len++;
		quote = check_quote(quote, pipe->line[len]);
	}
	len -= start;
	pipe->arg[arg] = (char *)malloc(len + 1);
	if (pipe->arg[arg] == NULL)
		exit_cmdl(cmdl, 1, false);
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

size_t	start_arg(char *str, size_t quote, size_t start)
{
	start++;
	if ((str[start - 1] == '<' && str[start] == '<')
		|| (str[start - 1] == '>' && str[start] == '>'))
		start++;
	while (space(str[start]) == true)
		start++;
	while (quote > 0 || (space(str[start]) == false
			&& str[start] != '<' && str[start] != '>'))
	{
		quote = check_quote(quote, str[start]);
		start++;
	}
	while (space(str[start]) == true)
		start++;
	return (start);
}

/* SPLITS ARGUMENTS */
void	split_arg(t_cmdl *cmdl, t_pipe *pipe)
{
	size_t	arg;
	size_t	start;
	size_t	len;
	size_t	quote;

	count_arg(cmdl, pipe);
	arg = 0;
	start = len_cmd(pipe);
	quote = check_quote(0, pipe->line[start]);
	while (arg < pipe->n_arg)
	{
		while (space(pipe->line[start]) == true)
			start++;
		if (!quote && (pipe->line[start] == '<' || pipe->line[start] == '>'))
			start = start_arg(pipe->line, quote, start);
		else
		{
			len = len_arg(cmdl, pipe, arg, start);
			copy_arg(pipe, arg, start, len);
			pipe->arg[arg] = remove_quote(cmdl, pipe->arg[arg]);
			start += len;
			arg++;
		}
	}
}
