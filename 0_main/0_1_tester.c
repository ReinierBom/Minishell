/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   0_1_tester.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/01 14:12:14 by rbom          #+#    #+#                 */
/*   Updated: 2024/10/11 17:48:02 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	test_parsing_cmdl(t_cmdl *cmdl)
{
	printf("\nINPUT:\t\t\t\t\t%s\n", cmdl->input);
	printf("N_CMD:\t\t\t\t\t%li\n", cmdl->n);
}

void	test_parsing_cmd(t_cmd *cmd)
{
	printf("\n\tCMD:\t\t\t\t%s\n", cmd->line);
	if (cmd->and_or == 0)
		printf("\t& / |:\t\t\t\tAND\n");
	else if (cmd->and_or == 1)
		printf("\t& / |:\t\t\t\tOR\n");
	printf("\tOPEN:\t\t\t\t%li\n", cmd->open);
	printf("\tCLOSE:\t\t\t\t%li\n", cmd->close);
}

void	test_parsing_pipe(t_cmd *cmd)
{
	size_t	pipe;
	size_t	arg;

	printf("\tN_PIPE:\t\t\t\t%li\n", cmd->n);
	pipe = 0;
	while (pipe < cmd->n)
	{
		printf("\t\tPIPE %li:\t\t\t%s\n", pipe + 1, cmd->pipe[pipe].line);
		if (cmd->pipe[pipe].cmd == NULL)
			printf("\t\t\t\tCMD:\tNULL\n");
		else if (cmd->pipe[pipe].cmd[0] == '\0')
			printf("\t\t\t\tCMD:\t\\0\n");
		else
			printf("\t\t\t\tCMD:\t%s\n", cmd->pipe[pipe].cmd);
		printf("\t\t\tN_ARSG:\t\t%li\n", cmd->pipe[pipe].n_arg);
		arg = 0;
		while (arg < cmd->pipe[pipe].n_arg)
		{
			printf("\t\t\t\tARG %li:\t%s\n", arg + 1, cmd->pipe[pipe].arg[arg]);
			arg++;
		}
		printf("\t\t\tN_RED:\t\t%li\n", cmd->pipe[pipe].n_red);
		arg = 0;
		while (arg < cmd->pipe[pipe].n_red)
		{
			if (cmd->pipe[pipe].red[arg] == 1)
				printf("\t\t\t\tRED %li:\tINPUT\n", arg + 1);
			else if (cmd->pipe[pipe].red[arg] == 2)
				printf("\t\t\t\tRED %li:\tHEREDOC\n", arg + 1);
			else if (cmd->pipe[pipe].red[arg] == 3)
				printf("\t\t\t\tRED %li:\tOUTPUT\n", arg + 1);
			else if (cmd->pipe[pipe].red[arg] == 4)
				printf("\t\t\t\tRED %li:\tAPPEND\n", arg + 1);
			if (cmd->pipe[pipe].red_arg[arg] == NULL)
				printf("\t\t\t\tR_A %li:\tNULL\n", arg + 1);
			else if (cmd->pipe[pipe].red_arg[arg][0] == '\0')
				printf("\t\t\t\tR_A %li:\t\\0\n", arg + 1);
			else
				printf("\t\t\t\tR_A %li:\t%s\n", arg + 1, cmd->pipe[pipe].red_arg[arg]);
			arg++;
		}
		pipe++;
	}
	printf("\n");
}
