/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   5_2_sub.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 14:37:56 by rbom          #+#    #+#                 */
/*   Updated: 2024/10/04 16:12:28 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* COUNTS PAR */
static size_t	count_sub(char *str)
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
static char	*remove_sub(t_cmdl *cmdl, char *str)
{
	size_t	len;
	char	*no_par;
	size_t	start;
	size_t	i;

	len = count_sub(str);
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
static void	sub_open_close(t_cmd *cmd)
{
	size_t	i;

	cmd->open = 0;
	cmd->close = 0;
	i = 0;
	while (cmd->line[i] != '\0' && (cmd->line[i] == '(' || space(cmd->line[i])))
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
void	subshell(t_cmdl *cmdl)
{
	size_t	cmd;

	cmd = 0;
	while (cmd < cmdl->n)
	{
		sub_open_close(&cmdl->cmd[cmd]);
		cmdl->sub += cmdl->cmd[cmd].open;
		cmdl->cmd[cmd].sub = cmdl->sub;
		cmdl->sub -= cmdl->cmd[cmd].close;
		cmdl->cmd[cmd].line = remove_sub(cmdl, cmdl->cmd[cmd].line);
		cmd++;
	}
}
