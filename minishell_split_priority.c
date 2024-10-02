/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_split_par.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 14:37:56 by rbom          #+#    #+#                 */
/*   Updated: 2024/09/13 18:40:01 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* COUNTS PAR */
static size_t	count_par(char *str)
{
	size_t	start;
	size_t	len;

	start = 0;
	len = 0;
	while (str[start] == '(' || space(str[start]))
		start++;
	while (str[start + len] != '\0')
		len++;
	while (len > 0 && (str[start + len - 1] == ')' || space(str[start + len - 1])))
		len--;
	return (len);	
}

/* REMOVES PAR */
static char	*remove_par(t_cmdl *cmdl, char *str)
{
	size_t	len;
	char	*no_par;
	size_t	start;
	size_t	i;

	len = count_par(str);
	no_par = (char *)malloc(len + 1);
	if (no_par == NULL)
		exit_cmdl(cmdl, 1);
	start = 0;
	i = 0;
	while (str[start] == '(' || space(str[start]))
		start++;
	while (i < len)
	{
		no_par[i] = str[start + i];
		i++;
	}
	no_par[len] = '\0';
	free(str);
	return (no_par);
}

/* SETS PRIORITY */
static void	prio_open_close(t_cmd *cmd)
{
	size_t	i;

	cmd->open = 0;
	cmd->close = 0;
	i = 0;
	while (cmd->line[i] == '(' || space(cmd->line[i]))
	{
		if (cmd->line[i] == '(')
			cmd->open++;
		i++;
	}
	while (cmd->line[i] != '\0')
		i++;
	while (i > 0 && (cmd->line[i - 1] == ')' || space(cmd->line[i - 1])))
	{
		if (cmd->line[i - 1] == ')')
			cmd->close++;
		i--;
	}
}

/* SETS PRIORITY */
void	prioritise(t_cmdl *cmdl)
{
	size_t	prio;
	size_t	cmd;

	prio = 0;
	cmd = 0;
	while (cmd < cmdl->n)
	{
		prio_open_close(&cmdl->cmd[cmd]);
		prio += cmdl->cmd[cmd].open;
		cmdl->cmd[cmd].priority = prio;
		prio -= cmdl->cmd[cmd].close;
		cmdl->cmd[cmd].line = remove_par(cmdl, cmdl->cmd[cmd].line);
		split_pipe(cmdl, &cmdl->cmd[cmd]);
		cmd++;
	}
}
