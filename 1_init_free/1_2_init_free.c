/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   1_2_init_free.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/01 14:12:14 by rbom          #+#    #+#                 */
/*   Updated: 2024/10/02 14:55:47 by rbom          ########   odam.nl         */
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

// void	free_cmdl(t_cmdl *cmdl)
// {
// 	size_t	cmd;
// 	size_t	pipe;
// 	size_t	arg;

// 	if (cmdl->input != NULL)
// 		free(cmdl->input);
// 	if (cmdl->cmd != NULL)
// 	{
// 		cmd = 0;
// 		while (cmd < cmdl->n)
// 		{
// 			if (cmdl->cmd[cmd].line != NULL)
// 				free(cmdl->cmd[cmd].line);
// 			if (cmdl->cmd[cmd].pipe != NULL)
// 			{
// 				pipe = 0;
// 				while (pipe < cmdl->cmd[cmd].n)
// 				{
// 					if (cmdl->cmd[cmd].pipe[pipe].line != NULL)
// 						free(cmdl->cmd[cmd].pipe[pipe].line);
// 					if (cmdl->cmd[cmd].pipe[pipe].cmd != NULL)
// 						free(cmdl->cmd[cmd].pipe[pipe].cmd);
// 					if (cmdl->cmd[cmd].pipe[pipe].arg != NULL)
// 					{
// 						arg = 0;
// 						while (arg < cmdl->cmd[cmd].pipe[pipe].n_arg)
// 						{
// 							if (cmdl->cmd[cmd].pipe[pipe].arg[arg] != NULL)
// 								free(cmdl->cmd[cmd].pipe[pipe].arg[arg]);
// 							arg++;
// 						}
// 						free(cmdl->cmd[cmd].pipe[pipe].arg);
// 					}
// 					if (cmdl->cmd[cmd].pipe[pipe].red != NULL)
// 						free(cmdl->cmd[cmd].pipe[pipe].red);
// 					if (cmdl->cmd[cmd].pipe[pipe].red_arg != NULL)
// 					{
// 						arg = 0;
// 						while (arg < cmdl->cmd[cmd].pipe[pipe].n_red)
// 						{
// 							if (cmdl->cmd[cmd].pipe[pipe].red_arg[arg] != NULL)
// 								free(cmdl->cmd[cmd].pipe[pipe].red_arg[arg]);
// 							arg++;
// 						}
// 						free(cmdl->cmd[cmd].pipe[pipe].red_arg);
// 					}
// 					pipe++;
// 				}
// 			}
// 			free(cmdl->cmd[cmd].pipe);
// 			cmd++;
// 		}
// 		free(cmdl->cmd);
// 	}
// }

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
			if (pipe->arg != NULL && pipe->arg[arg] != NULL)
				free(pipe->arg[arg]);
			if (pipe->red_arg != NULL && pipe->red_arg[arg] != NULL)
				free(pipe->red_arg[arg]);
			arg++;
		}
		free(pipe->arg);
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

void	exit_cmdl(t_cmdl *cmdl, size_t exit_code)
{
	free_cmdl(cmdl);
	if (cmdl->env != NULL)
		free(cmdl->env);
	rl_clear_history();
	exit(exit_code);
}
