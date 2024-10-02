/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_split_pipe.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 14:37:56 by rbom          #+#    #+#                 */
/*   Updated: 2024/09/13 18:44:16 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* COUNTS PIPES */
static void	count_pipe(t_cmdl *cmdl, t_cmd *cmd)
{
	size_t	i;
	size_t	quote;

	i = 0;
	quote = 0;
	cmd->n = 1;
	while (quote > 0 || cmd->line[i] != '\0')
	{
		quote = check_quote(quote, cmd->line[i]);
		if (quote == 0 && cmd->line[i] == '|')
			cmd->n++;
		i++;
	}
	cmd->pipe = (t_pipe *)malloc(cmd->n * sizeof(t_pipe));
	if (cmd->pipe == NULL)
		exit_cmdl(cmdl, 1);
	init_pipe(cmd);
}

/* LENGTH PIPE */
size_t	len_pipe(t_cmdl *cmdl, t_cmd *cmd, size_t pipe, size_t start)
{
	size_t	len;
	size_t	quote;

	len = 0;
	quote = check_quote(0, cmd->line[start]);
	while ((quote > 0 || (cmd->line[start + len] != '|' && cmd->line[start + len] != '\0')))
	{
		len++;
		quote = check_quote(quote, cmd->line[start + len]);
	}
	cmd->pipe[pipe].line = (char *)malloc(len + 1);
	if (cmd->pipe[pipe].line == NULL)
		exit_cmdl(cmdl, 1);
	return (len);
}

/* COPIES PIPE */
void	copy_pipe(t_cmdl *cmdl, t_cmd *cmd, size_t pipe, size_t start)
{
	size_t	len;
	size_t	quote;

	len = 0;
	quote = check_quote(0, cmd->line[start]);
	while ((quote > 0 || (cmd->line[start + len] != '|' && cmd->line[start + len] != '\0')))
	{
		cmd->pipe[pipe].line[len] = cmd->line[start + len];
		len++;
		quote = check_quote(quote, cmd->line[start + len]);
	}
	cmd->pipe[pipe].line[len] = '\0';
	cmd->pipe[pipe].line = remove_space(cmdl, cmd->pipe[pipe].line);
}

/* SPLITS COMMANDS INTO PIPES */
void	split_pipe(t_cmdl *cmdl, t_cmd *cmd)
{
	size_t	pipe;
	size_t	start;
	size_t	len;

	count_pipe(cmdl, cmd);
	pipe = 0;
	start = 0;
	while (pipe < cmd->n)
	{
		len = len_pipe(cmdl, cmd, pipe, start);
		copy_pipe(cmdl, cmd, pipe, start);
		copy_cmd(cmdl, &cmd->pipe[pipe]);
		split_arg(cmdl, &cmd->pipe[pipe]);
		// count_red(cmdl, &cmd->pipe[pipe]);
		copy_red(cmdl, &cmd->pipe[pipe]);
		split_red_arg(cmdl, &cmd->pipe[pipe]);
		start += len + 1;
		pipe++;
	}
}
