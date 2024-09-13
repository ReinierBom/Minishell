/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_split_and_or.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 14:37:56 by rbom          #+#    #+#                 */
/*   Updated: 2024/09/13 19:01:51 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* CHECKS IF && OR || */
size_t	check_and_or(char *str, size_t i)
{
	if (str[i] == '&' && str[i + 1] == '&')
		return (1);
	else if (str[i] == '|' && str[i + 1] == '|')
		return (2);
	else
		return (0);
}

/* COUNTS COMMANDS */
void	count_and_or(t_cmdl *cmdl)
{
	size_t	i;
	size_t	quote;
	size_t	and_or;

	i = 0;
	quote = 0;
	cmdl->n = 1;
	while (quote > 0 || cmdl->no_par[i] != '\0')
	{
		quote = check_quote(quote, cmdl->no_par[i]);
		and_or = check_and_or(cmdl->no_par, i);
		if (quote == 0 && and_or > 0)
		{
			cmdl->n++;
			i++;
		}
		i++;
	}
	cmdl->cmd = (t_cmd *)malloc(cmdl->n * sizeof(t_cmd));
	if (cmdl->cmd == NULL)
		exit_cmdl(cmdl, 1);
}

/* LENGTH COMMAND */
size_t	len_and_or(t_cmdl *cmdl, size_t cmd, size_t start)
{
	size_t	len;
	size_t	quote;
	size_t	and_or;

	len = 0;
	quote = check_quote(0, cmdl->no_par[start]);
	and_or = check_and_or(cmdl->no_par, start);
	while ((quote > 0 || (and_or == 0 && cmdl->no_par[start + len] != '\0')))
	{
		len++;
		quote = check_quote(quote, cmdl->no_par[start + len]);
		and_or = check_and_or(cmdl->no_par, start + len);
	}
	cmdl->cmd[cmd].raw = (char *)malloc(len + 1);
	if (cmdl->cmd[cmd].raw == NULL)
		exit_cmdl(cmdl, 1);
	return (len);
}

/* COPIES COMMAND */
void	copy_and_or(t_cmdl *cmdl, size_t cmd, size_t start)
{
	size_t	len;
	size_t	quote;
	size_t	and_or;

	len = 0;
	quote = check_quote(0, cmdl->no_par[start]);
	and_or = check_and_or(cmdl->no_par, start);
	while (quote > 0 || (and_or == 0 && cmdl->no_par[start + len] != '\0'))
	{
		cmdl->cmd[cmd].raw[len] = cmdl->no_par[start + len];
		len++;
		quote = check_quote(quote, cmdl->no_par[start + len]);
		and_or = check_and_or(cmdl->no_par, start + len);
	}
	cmdl->cmd[cmd].raw[len] = '\0';
}

/* SPLITS COMMAND LINE INTO COMMANDS */
void	split_and_or(t_cmdl *cmdl)
{
	size_t	cmd;
	size_t	start;
	size_t	len;

	cmd = 0;
	start = 0;
	while (cmd < cmdl->n)
	{
		if (cmd == 0)
			cmdl->cmd[cmd].and_or = 1;
		else
		{
			cmdl->cmd[cmd].and_or = check_and_or(cmdl->no_par, start);
			start += 2;
		}
		len = len_and_or(cmdl, cmd, start);
		copy_and_or(cmdl, cmd, start);
		start += len;
		cmd++;
	}
}
