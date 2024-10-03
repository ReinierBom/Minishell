/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   1_init.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/01 14:12:14 by rbom          #+#    #+#                 */
/*   Updated: 2024/10/02 14:15:56 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_start(t_cmdl *cmdl, char **envp)
{
	cmdl->pid = 1;
	g_signal = 0;
	copy_ev(cmdl, envp);
	add_replace_ev(cmdl, "?=0");
}

void	init_cmdl(t_cmdl *cmdl)
{
	// signal_mode(cmdl, true);
	cmdl->sub = 0;
	cmdl->input = NULL;
	cmdl->n = 0;
	cmdl->cmd = NULL;
}

void	init_cmd(t_cmdl *cmdl)
{
	size_t	cmd;

	cmd = 0;
	while (cmd < cmdl->n)
	{
		cmdl->cmd[cmd].and_or = 0;
		cmdl->cmd[cmd].open = 0;
		cmdl->cmd[cmd].sub = 0;
		cmdl->cmd[cmd].close = 0;
		cmdl->cmd[cmd].line = NULL;
		cmdl->cmd[cmd].n = 0;
		cmdl->cmd[cmd].pipe = NULL;
		cmd++;
	}
}

void	init_pipe(t_cmd *cmd)
{
	size_t	pipe;

	pipe = 0;
	while (pipe < cmd->n)
	{
		cmd->pipe[pipe].line = NULL;
		cmd->pipe[pipe].cmd = NULL;
		cmd->pipe[pipe].n_arg = 0;
		cmd->pipe[pipe].arg = NULL;
		cmd->pipe[pipe].n_red = 0;
		cmd->pipe[pipe].red = NULL;
		cmd->pipe[pipe].red_arg = NULL;
		pipe++;
	}
}

void	init_arg(t_pipe *pipe)
{
	size_t	arg;

	arg = 0;
	while (arg < pipe->n_arg)
	{
		pipe->arg[arg] = NULL;
		arg++;
	}
}
