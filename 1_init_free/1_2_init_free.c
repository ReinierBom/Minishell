/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   1_2_init_free.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/01 14:12:14 by rbom          #+#    #+#                 */
/*   Updated: 2024/10/11 17:43:29 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static void	free_pipe(t_pipe *pipe)
{
	size_t	arg;

	if (pipe->line != NULL)
		free(pipe->line);
	if (pipe->cmd != NULL)
		free(pipe->cmd);
	if (pipe->red != NULL)
		free(pipe->red);
	if (pipe->arg != NULL || pipe->red_arg != NULL)
	{
		arg = 0;
		while (arg < pipe->n_arg || arg < pipe->n_red)
		{
			if (arg < pipe->n_arg && pipe->arg && pipe->arg[arg])
				free(pipe->arg[arg]);
			if (arg < pipe->n_red && pipe->red_arg && pipe->red_arg[arg])
				free(pipe->red_arg[arg]);
			arg++;
		}
		if (pipe->arg != NULL)
			free(pipe->arg);
		if (pipe->red_arg != NULL)
			free(pipe->red_arg);
	}
}

void	free_cmdl(t_cmdl *cmdl)
{
	size_t	cmd;
	size_t	pipe;

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
					free_pipe(&cmdl->cmd[cmd].pipe[pipe++]);
			}
			free(cmdl->cmd[cmd++].pipe);
		}
		free(cmdl->cmd);
	}
}

void	exit_cmdl(t_cmdl *cmdl, size_t exit_code, bool message)
{
	if (message == true)
		printf("exit\n");
	free_cmdl(cmdl);
	if (cmdl->env != NULL)
		free(cmdl->env);
	rl_clear_history();
	exit(exit_code);
}
