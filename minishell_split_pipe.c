/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_split_pipe.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 14:37:56 by rbom          #+#    #+#                 */
/*   Updated: 2024/09/12 15:28:21 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_pipe(t_cmdl *cmdl)
{
	size_t	i;
	size_t	cmd;
	size_t	quote;

	cmd = 0;
	while (cmd < cmdl->n)
	{
		i = 0;
		quote = 0;
		cmdl->cmd[cmd].n = 1;
		while (quote > 0 || cmdl->cmd[cmd].raw[i] != '\0')
		{
			quote = check_quote(quote, cmdl->cmd[cmd].raw[i]);
			if (quote == 0 && cmdl->cmd[cmd].raw[i] == '|')
				cmdl->cmd[cmd].n++;
			i++;
		}
		cmdl->cmd[cmd].p = (t_pipe *)malloc(cmdl->cmd[cmd].n * sizeof(t_pipe));
		if (cmdl->cmd[cmd].p == NULL)
			exit_cmdl(cmdl, 1);
		cmd++;
	}
}

size_t	len_pipe(t_cmdl *cmdl, size_t cmd, size_t p, size_t start)
{
	size_t	len;
	size_t	quote;

	len = 0;
	quote = check_quote(0, cmdl->cmd[cmd].raw[start]);
	while ((quote > 0 || (cmdl->cmd[cmd].raw[start + len] != '|' && cmdl->cmd[cmd].raw[start + len] != '\0')))
	{
		len++;
		quote = check_quote(quote, cmdl->cmd[cmd].raw[start + len]);
	}
	cmdl->cmd[cmd].p[p].raw = (char *)malloc(len + 1);
	if (cmdl->cmd[cmd].p[p].raw == NULL)
		exit_cmdl(cmdl, 1);
	return (len);
}

void	copy_pipe(t_cmdl *cmdl, size_t cmd, size_t p, size_t start)
{
	size_t	len;
	size_t	quote;

	len = 0;
	quote = check_quote(0, cmdl->cmd[cmd].raw[start]);
	while ((quote > 0 || (cmdl->cmd[cmd].raw[start + len] != '|' && cmdl->cmd[cmd].raw[start + len] != '\0')))
	{
		cmdl->cmd[cmd].p[p].raw[len] = cmdl->cmd[cmd].raw[start + len];
		len++;
		quote = check_quote(quote, cmdl->cmd[cmd].raw[start + len]);
	}
	cmdl->cmd[cmd].p[p].raw[len] = '\0';
}

void	split_pipe(t_cmdl *cmdl)
{
	size_t	cmd;
	size_t	p;
	size_t	start;
	size_t	len;

	cmd = 0;
	while (cmd < cmdl->n)
	{
		p = 0;
		start = 0;
		while (p < cmdl->cmd->n)
		{
			len = len_pipe(cmdl, cmd, p, start);
			copy_pipe(cmdl, cmd, p, start);
			start += len + 1;
			p++;
		}
		cmd++;
	}
}
