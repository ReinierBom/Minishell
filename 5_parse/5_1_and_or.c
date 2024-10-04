/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   5_1_and_or.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 14:37:56 by rbom          #+#    #+#                 */
/*   Updated: 2024/10/04 15:02:41 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* CHECKS IF && OR || */
static size_t	check_and_or(char *str, size_t i)
{
	if (str[i] == '&' && str[i + 1] == '&')
		return (1);
	else if (str[i] == '|' && str[i + 1] == '|')
		return (2);
	else
		return (0);
}

/* COUNTS COMMANDS */
static void	count_and_or(t_cmdl *cmdl)
{
	size_t	i;
	size_t	quote;
	size_t	and_or;

	i = 0;
	quote = 0;
	cmdl->n = 1;
	while (quote > 0 || cmdl->input[i] != '\0')
	{
		quote = check_quote(quote, cmdl->input[i]);
		and_or = check_and_or(cmdl->input, i);
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
	init_cmd(cmdl);
}

/* LENGTH COMMAND */
static size_t	len_and_or(t_cmdl *cmdl, size_t cmd, size_t start)
{
	size_t	len;
	size_t	quote;
	size_t	and_or;

	len = 0;
	quote = check_quote(0, cmdl->input[start]);
	and_or = check_and_or(cmdl->input, start);
	while ((quote > 0 || (and_or == 0 && cmdl->input[start + len] != '\0')))
	{
		len++;
		quote = check_quote(quote, cmdl->input[start + len]);
		and_or = check_and_or(cmdl->input, start + len);
	}
	cmdl->cmd[cmd].line = (char *)malloc(len + 1);
	if (cmdl->cmd[cmd].line == NULL)
		exit_cmdl(cmdl, 1);
	return (len);
}

/* COPIES COMMAND */
static void	copy_and_or(t_cmdl *cmdl, size_t cmd, size_t start)
{
	size_t	len;
	size_t	quote;
	size_t	and_or;

	len = 0;
	quote = check_quote(0, cmdl->input[start]);
	and_or = check_and_or(cmdl->input, start);
	while (quote > 0 || (and_or == 0 && cmdl->input[start + len] != '\0'))
	{
		cmdl->cmd[cmd].line[len] = cmdl->input[start + len];
		len++;
		quote = check_quote(quote, cmdl->input[start + len]);
		and_or = check_and_or(cmdl->input, start + len);
	}
	cmdl->cmd[cmd].line[len] = '\0';
	cmdl->cmd[cmd].line = split_env_var(cmdl, cmdl->cmd[cmd].line);
	cmdl->cmd[cmd].line = remove_space(cmdl, cmdl->cmd[cmd].line);
}

/* SPLITS COMMAND LINE INTO COMMANDS */
void	parse_cmdl(t_cmdl *cmdl)
{
	size_t	cmd;
	size_t	start;
	size_t	len;

	count_and_or(cmdl);
	cmd = 0;
	start = 0;
	while (cmd < cmdl->n)
	{
		if (cmd == 0)
			cmdl->cmd[cmd].and_or = 0;
		else
		{
			cmdl->cmd[cmd].and_or = check_and_or(cmdl->input, start) - 1;
			start += 2;
		}
		len = len_and_or(cmdl, cmd, start);
		copy_and_or(cmdl, cmd, start);
		start += len;
		cmd++;
	}
	subshell(cmdl);
}
