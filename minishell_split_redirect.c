/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_split_redirect.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 14:37:56 by rbom          #+#    #+#                 */
/*   Updated: 2024/09/13 19:01:14 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* LENGTH COMMAND ARG, NOT WORKING YET! */
void	len_cmd(t_cmdl *cmdl)
{
	size_t	cmd;
	size_t	p;
	size_t	i;
	size_t	len;
	size_t	quote;

	cmd = 0;
	while (cmd < cmdl->n)
	{
		p = 0;
		while (p < cmdl->cmd[cmd].n)
		{
			i = 0;
			len = 0;
			quote = check_quote(0, cmdl->cmd[cmd].p[p].raw[i]);
			while (space(cmdl->cmd[cmd].p[p].raw[i]) == true)
				i++;
			// printf("%c\t%i\n", cmdl->cmd[cmd].p[p].raw[i], cmdl->cmd[cmd].p[p].raw[i]);
			while (quote > 0 || space(cmdl->cmd[cmd].p[p].raw[i]) == false)
			{
				// quote = check_quote(quote, cmdl->cmd[cmd].p[p].raw[i]);
				i++;
				// len++;
			}
			// cmdl->cmd[cmd].p[p].cmd = (char *)malloc(len + 1);
			// if (cmdl->cmd[cmd].p[p].cmd == NULL)
			// 	exit_cmdl(cmdl, 1);
			// printf("LEN:\t%li\n", len);
			p++;
		}
		cmd++;
	}
}

/* COPIES COMMAND ARG, NOT WORKING YET! */
void	copy_cmd(t_cmdl *cmdl)
{
	size_t	cmd;
	size_t	p;
	size_t	i;
	size_t	j;
	size_t	quote;

	cmd = 0;
	while (cmd < cmdl->n)
	{
		p = 0;
		while (p < cmdl->cmd[cmd].n)
		{
			i = 0;
			j = 0;
			quote = check_quote(0, cmdl->cmd[cmd].p[p].raw[i]);
			while (space(cmdl->cmd[cmd].p[p].raw[i]) == false)
				i++;
			while (quote > 0 || space(cmdl->cmd[cmd].p[p].raw[i]) == true)
			{
				cmdl->cmd[cmd].p[p].cmd[j] = cmdl->cmd[cmd].p[p].raw[i];
				quote = check_quote(quote, cmdl->cmd[cmd].p[p].raw[i]);
				i++;
				j++;
			}
			cmdl->cmd[cmd].p[p].cmd[j] = '\0';
			p++;
		}
		cmd++;
	}
}

/* COUNTS ARGS, NOT WORKING YET! */
void	count_arg(t_cmdl *cmdl)
{
	size_t	cmd;
	size_t	p;
	size_t	i;
	size_t	quote;

	cmd = 0;
	while (cmd < cmdl->n)
	{
		p = 0;
		while (p < cmdl->cmd[cmd].n)
		{
			i = 0;
			quote = 0;
			cmdl->cmd[cmd].p[p].n_arg = 0;
			while (quote > 0 || (cmdl->cmd[cmd].p[p].raw[i] != '<' && cmdl->cmd[cmd].p[p].raw[i] != '>' && cmdl->cmd[cmd].p[p].raw[i] != '\0'))
			{
				if (i > 0 && space(cmdl->cmd[cmd].p[p].raw[i - 1]) == true && space(cmdl->cmd[cmd].p[p].raw[i]) == false)
					cmdl->cmd[cmd].p[p].n_arg++;
				quote = check_quote(quote, cmdl->cmd[cmd].p[p].raw[i]);
				i++;
			}
			p++;
		}
		cmd++;
	}
}

/* COUNTS REDIRECTS */
// void	count_red(t_cmdl *cmdl)
// {
// 	size_t	quote;
	
// }
