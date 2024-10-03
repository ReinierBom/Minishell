/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   5_7_red_arg.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 14:37:56 by rbom          #+#    #+#                 */
/*   Updated: 2024/10/02 17:34:10 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* START REDIRECT ARGUMENTS */
static size_t	start_red_arg(char *line, size_t start)
{
	while (space(line[start]) == true)
		start++;
	if (check_red(line, start) == 1 || check_red(line, start) == 3)
		start += 1;
	else if (check_red(line, start) == 2 || check_red(line, start) == 4)
		start += 2;
	while (space(line[start]) == true)
		start++;
	return (start);
}

/* LEN REDIRECT ARGUMENTS */
static size_t	len_red_arg(t_cmdl *cmdl, t_pipe *pipe, size_t red, size_t s)
{
	size_t	len;
	size_t	quote;

	quote = check_quote(0, pipe->line[s]);
	len = 0;
	while (quote > 0 || (check_red(pipe->line, s + len) == 0 && space(pipe->line[s + len]) == false && pipe->line[s + len] != '\0'))
	{
		len++;
		quote = check_quote(quote, pipe->line[s + len]);
	}
	pipe->red_arg[red] = malloc(len + 1);
	if (pipe->red_arg[red] == NULL)
		exit_cmdl(cmdl, 1);
	return (len);
	init_red_arg(pipe);
}

/* COPIES REDIRECT ARGUMENTS */
static void	copy_red_arg(t_pipe *pipe, size_t red, size_t start)
{
	size_t	len;
	size_t	quote;

	quote = check_quote(0, pipe->line[start]);
	len = 0;
	while (quote > 0 || (check_red(pipe->line, start) == 0 && space(pipe->line[start]) == false && pipe->line[start] != '\0'))
	{
		pipe->red_arg[red][len] = pipe->line[start];
		start++;
		len++;
		quote = check_quote(quote, pipe->line[start]);
	}
	pipe->red_arg[red][len] = '\0';
}

/* SPLITS REDIRECT ARGUMENTS */
void	split_red_arg(t_cmdl *cmdl, t_pipe *pipe)
{
	size_t	start;
	size_t	len;
	size_t	red;

	start = start_red(pipe);
	red = 0;
	while (red < pipe->n_red)
	{
		start = start_red_arg(pipe->line, start);
		len = len_red_arg(cmdl, pipe, red, start);
		copy_red_arg(pipe, red, start);
		pipe->red_arg[red] = split_env_var(cmdl, pipe->red_arg[red]);
		pipe->red_arg[red] = remove_quote(cmdl, pipe->red_arg[red]);
		start += len;
		red++;
	}
}
