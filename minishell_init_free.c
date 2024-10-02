/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_free.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/01 14:12:14 by rbom          #+#    #+#                 */
/*   Updated: 2024/09/12 21:16:05 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmdl(t_cmdl *cmdl)
{
	g_signal = 0;
	// signal_mode(cmdl, true);
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
		cmdl->cmd[cmd].priority = 0;
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

void	init_red_arg(t_pipe *pipe)
{
	size_t	red;

	red = 0;
	while (red < pipe->n_red)
	{
		pipe->red_arg[red] = NULL;
		red++;
	}
}

void	free_cmdl(t_cmdl *cmdl)
{
	size_t	cmd;
	size_t	pipe;
	size_t	arg;

	if (cmdl->input != NULL)
		free(cmdl->input);
	if (cmdl->cmd != NULL)
	{
		cmd = 0;
		while (cmd < cmdl->n)
		{
			if (cmdl->cmd[cmd].line != NULL)
				free(cmdl->cmd[cmd].line);
			if (cmdl->cmd[cmd].pipe != NULL)
			{
				pipe = 0;
				while (pipe < cmdl->cmd[cmd].n)
				{
					if (cmdl->cmd[cmd].pipe[pipe].line != NULL)
						free(cmdl->cmd[cmd].pipe[pipe].line);
					if (cmdl->cmd[cmd].pipe[pipe].cmd != NULL)
						free(cmdl->cmd[cmd].pipe[pipe].cmd);
					if (cmdl->cmd[cmd].pipe[pipe].arg != NULL)
					{
						arg = 0;
						while (arg < cmdl->cmd[cmd].pipe[pipe].n_arg)
						{
							if (cmdl->cmd[cmd].pipe[pipe].arg[arg] != NULL)
								free(cmdl->cmd[cmd].pipe[pipe].arg[arg]);
							arg++;
						}
						free(cmdl->cmd[cmd].pipe[pipe].arg);			
					}
					if (cmdl->cmd[cmd].pipe[pipe].red != NULL)
						free(cmdl->cmd[cmd].pipe[pipe].red);
					if (cmdl->cmd[cmd].pipe[pipe].red_arg != NULL)
					{
						arg = 0;
						while (arg < cmdl->cmd[cmd].pipe[pipe].n_red)
						{
							if (cmdl->cmd[cmd].pipe[pipe].red_arg[arg] != NULL)
								free(cmdl->cmd[cmd].pipe[pipe].red_arg[arg]);
							arg++;
						}
						free(cmdl->cmd[cmd].pipe[pipe].red_arg);
					}
					pipe++;
				}
			}
			free(cmdl->cmd[cmd].pipe);
			cmd++;
		}
		free(cmdl->cmd);
	}
}

void	exit_cmdl(t_cmdl *cmdl, size_t exit_code)
{
	free_cmdl(cmdl);
	if (cmdl->env != NULL)
		free(cmdl->env);
	rl_clear_history();
	exit(exit_code);
}
