/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_main.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/01 14:12:14 by rbom          #+#    #+#                 */
/*   Updated: 2024/09/13 19:03:37 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

/* TEST VOOR PARSING */
void	test_parsing(t_cmdl *cmdl)
{
	size_t	cmd;
	size_t	pipe;
	size_t	arg;

	split_and_or(cmdl);
	printf("\nINPUT:\t\t\t\t\t%s\n", cmdl->input);
	printf("N_CMD:\t\t\t\t\t%li\n", cmdl->n);
	cmd = 0;
	while (cmd < cmdl->n)
	{
		printf("\n\tCMD %li:\t\t\t\t%s\n", cmd + 1, cmdl->cmd[cmd].line);
		if (cmdl->cmd[cmd].and_or == 0)
			printf("\t& / |:\t\t\t\tAND\n");
		else if (cmdl->cmd[cmd].and_or == 1)
			printf("\t& / |:\t\t\t\tOR\n");
		printf("\tOPEN:\t\t\t\t%li\n", cmdl->cmd[cmd].open);
		printf("\tPRIO:\t\t\t\t%li\n", cmdl->cmd[cmd].priority);
		printf("\tCLOSE:\t\t\t\t%li\n", cmdl->cmd[cmd].close);
		printf("\tN_PIPE:\t\t\t\t%li\n", cmdl->cmd[cmd].n);
		pipe = 0;
		while (pipe < cmdl->cmd[cmd].n)
		{
			printf("\t\tPIPE %li:\t\t\t%s\n", pipe + 1, cmdl->cmd[cmd].pipe[pipe].line);
			printf("\t\t\t\tCMD:\t%s\n", cmdl->cmd[cmd].pipe[pipe].cmd);
			printf("\t\t\tN_RAG:\t\t%li\n", cmdl->cmd[cmd].pipe[pipe].n_arg);
			arg = 0;
			while (arg < cmdl->cmd[cmd].pipe[pipe].n_arg)
			{
				printf("\t\t\t\tARG %li:\t%s\n", arg + 1, cmdl->cmd[cmd].pipe[pipe].arg[arg]);
				arg++;
			}
			printf("\t\t\tN_RED:\t\t%li\n", cmdl->cmd[cmd].pipe[pipe].n_red);
			arg = 0;
			while (arg < cmdl->cmd[cmd].pipe[pipe].n_red)
			{
				if (cmdl->cmd[cmd].pipe[pipe].red[arg] == 1)
					printf("\t\t\t\tRED %li:\tINPUT\n", arg + 1);
				else if (cmdl->cmd[cmd].pipe[pipe].red[arg] == 2)
					printf("\t\t\t\tRED %li:\tHEREDOC\n", arg + 1);
				else if (cmdl->cmd[cmd].pipe[pipe].red[arg] == 3)
					printf("\t\t\t\tRED %li:\tOUTPUT\n", arg + 1);
				else if (cmdl->cmd[cmd].pipe[pipe].red[arg] == 4)
					printf("\t\t\t\tRED %li:\tAPPEND\n", arg + 1);
				printf("\t\t\t\tR_A %li:\t%s\n", arg + 1, cmdl->cmd[cmd].pipe[pipe].red_arg[arg]);
				arg++;
			}
			pipe++;
		}
		cmd++;
	}
	printf("\n");
}

int	main(int argc, char **argv, char **envp)
{
	t_cmdl	cmdl;

	copy_ev(&cmdl, envp);
	/* init ?=0 and g_signal */
	while (argc != 0 && argv[0] != NULL)
	{
		init_cmdl(&cmdl);
		cmdl.input = readline("MINISHELL> ");
		add_history(cmdl.input);
		if (empty_line(&cmdl) == false)
		{
			test_parsing(&cmdl);
			// cmdl.input = split_env_var(&cmdl, cmdl.input);
			// printf("%s\n", cmdl.input);
		}
		free_cmdl(&cmdl);
	}
}
