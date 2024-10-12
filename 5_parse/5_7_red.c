/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   5_7_red.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 14:37:56 by rbom          #+#    #+#                 */
/*   Updated: 2024/10/11 17:32:51 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* CHECKS IF RED */
size_t	check_red(char *str, size_t i)
{
	if (str[i] == '<' && str[i + 1] == '<')
		return (2);
	else if (str[i] == '<')
		return (1);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (4);
	else if (str[i] == '>')
		return (3);
	else
		return (0);
}

/* COUNTS REDIRECTS */
static void	count_red(t_cmdl *cmdl, t_pipe *pipe)
{
	size_t	i;
	size_t	quote;

	i = 0;
	quote = check_quote(0, pipe->line[i]);
	while (quote > 0 || pipe->line[i] != '\0')
	{
		if (quote == 0 && check_red(pipe->line, i) > 0)
		{
			pipe->n_red++;
			if (check_red(pipe->line, i) == 2 || check_red(pipe->line, i) == 4)
				i++;
		}
		i++;
		quote = check_quote(quote, pipe->line[i]);
	}
	pipe->red = (size_t *)malloc(pipe->n_red * sizeof(size_t));
	if (pipe->red == NULL)
		exit_cmdl(cmdl, 1, false);
	pipe->red_arg = (char **)malloc(pipe->n_red * sizeof(char *));
	if (pipe->red_arg == NULL)
		exit_cmdl(cmdl, 1, false);
	init_red_arg(pipe);
}

/* COPIES REDIRECTS */
void	copy_red(t_cmdl *cmdl, t_pipe *pipe)
{
	size_t	i;
	size_t	red;
	size_t	quote;

	count_red(cmdl, pipe);
	i = 0;
	red = 0;
	quote = check_quote(0, pipe->line[i]);
	while (quote > 0 || pipe->line[i] != '\0')
	{
		if (quote == 0 && check_red(pipe->line, i) > 0)
		{
			pipe->red[red] = check_red(pipe->line, i);
			if (pipe->red[red] == 2 || pipe->red[red] == 4)
				i++;
			red++;
		}
		i++;
		quote = check_quote(quote, pipe->line[i]);
	}
}
