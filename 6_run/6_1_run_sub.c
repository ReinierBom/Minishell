/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   6_1_run_sub.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/01 14:12:14 by rbom          #+#    #+#                 */
/*   Updated: 2024/10/12 21:06:34 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	comp(char *str_1, char *str_2)
{
	size_t	i;

	i = 0;
	while (true)
	{
		if (str_1[i] == '\0' || str_2[i] == '\0' || str_1[i] != str_2[i])
			return (str_1[i] - str_2[i]);
		i++;
	}
}

static void	function_router(t_cmdl *cmdl, t_cmd *cmd)
{
	size_t	temp;

	temp = cmdl->n;
	temp++;
	if (cmd->pipe[0].cmd != NULL && comp(cmd->pipe[0].cmd, "echo") == 0)
		printf("ECHO\n");
	else if (cmd->pipe[0].cmd != NULL && comp(cmd->pipe[0].cmd, "cd") == 0)
		printf("CD\n");
	else if (cmd->pipe[0].cmd != NULL && comp(cmd->pipe[0].cmd, "pwd") == 0)
		printf("PWD\n");
	else if (cmd->pipe[0].cmd != NULL && comp(cmd->pipe[0].cmd, "export") == 0)
		printf("EXPORT\n");
	else if (cmd->pipe[0].cmd != NULL && comp(cmd->pipe[0].cmd, "unset") == 0)
		printf("UNSET\n");
	else if (cmd->pipe[0].cmd != NULL && comp(cmd->pipe[0].cmd, "env") == 0)
		printf("ENV\n");
	else if (cmd->pipe[0].cmd != NULL && comp(cmd->pipe[0].cmd, "exit") == 0)
		printf("EXIT\n");
	else
		printf("ELSE\n");																		/* <<< HIER INVOEGEN!!! <<< */
}

void	run_sub(t_cmdl *cmdl)
{
	size_t	cmd;
	
	cmd = 0;
	while (cmd < cmdl->n)
	{
		while (cmdl->cmd[cmd].open > 0)
		{
			if (cmdl->sub == cmdl->sub_cmd && ((g_exit == 0 && cmdl->cmd[cmd].and_or == 0) || (g_exit != 0 && cmdl->cmd[cmd].and_or != 0)) && fork() == 0)
				cmdl->sub_cmd++;
			cmdl->sub++;
			cmdl->cmd[cmd].open--;
		}
		if (cmdl->sub_cmd == cmdl->sub)
		{
			test_parsing_cmd(&cmdl->cmd[cmd]);
			if ((g_exit == 0 && cmdl->cmd[cmd].and_or == 0) || (g_exit != 0 && cmdl->cmd[cmd].and_or != 0))
			{
				parse_cmd(cmdl, &cmdl->cmd[cmd]);
				test_parsing_pipe(&cmdl->cmd[cmd]);
				function_router(cmdl, &cmdl->cmd[cmd]);
			}
		}
		else
			waitpid(0, NULL, 0);
		while (cmdl->cmd[cmd].close > 0)
		{
			if (cmdl->sub_cmd == cmdl->sub)
				exit_cmdl(cmdl, 0, false);
			cmdl->sub--;
			cmdl->cmd[cmd].close--;
		}			
		cmd++;
	}
}
