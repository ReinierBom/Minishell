/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   5_8_red_arg.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 14:37:56 by rbom          #+#    #+#                 */
/*   Updated: 2024/10/12 20:57:42 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* START REDIRECT ARGUMENTS */
static size_t	start_red_arg(char *line, size_t start)
{
	while (check_red(line, start) == 0)
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

	len = s;
	quote = check_quote(0, pipe->line[len]);
	while (quote > 0 || (check_red(pipe->line, len) == 0
			&& space(pipe->line[len]) == false && pipe->line[len] != '\0'))
	{
		len++;
		quote = check_quote(quote, pipe->line[len]);
	}
	len -= s;
	if (len == 0)
		return (len);
	pipe->red_arg[red] = malloc(len + 1);
	if (pipe->red_arg[red] == NULL)
		exit_cmdl(cmdl, 1, false);
	return (len);
}

/* COPIES REDIRECT ARGUMENTS */
static void	copy_red_arg(t_pipe *pipe, size_t red, size_t start, size_t len)
{
	size_t	i;
	size_t	quote;

	quote = check_quote(0, pipe->line[start]);
	i = 0;
	while (i < len)
	{
		pipe->red_arg[red][i] = pipe->line[start + i];
		i++;
		quote = check_quote(quote, pipe->line[start + i]);
	}
	pipe->red_arg[red][i] = '\0';
}

/* SPLITS REDIRECT ARGUMENTS */
void	split_red_arg(t_cmdl *cmdl, t_pipe *pipe)
{
	size_t	start;
	size_t	len;
	size_t	red;

	start = 0;
	red = 0;
	while (red < pipe->n_red)
	{
		start = start_red_arg(pipe->line, start);
		len = len_red_arg(cmdl, pipe, red, start);
		if (len > 0)
		{
			copy_red_arg(pipe, red, start, len);
			pipe->red_arg[red] = remove_quote(cmdl, pipe->red_arg[red]);
		}
		start += len;
		red++;
	}
}
