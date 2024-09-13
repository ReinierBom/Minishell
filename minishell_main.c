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

// /* TEST VOOR PARSING */
void	test_parsing(t_cmdl *cmdl)
{
	size_t	cmd;
	size_t	p;

	remove_par(cmdl);
	count_and_or(cmdl);
	split_and_or(cmdl);
	count_pipe(cmdl);
	split_pipe(cmdl);
	// len_cmd(cmdl);
	// copy_cmd(cmdl);
	count_arg(cmdl);



	printf("\nINPUT:\t\t\t\t%s\n", cmdl->input);
	printf("\nNO_PAR:\t\t\t\t%s\n", cmdl->no_par);
	cmd = 0;
	while (cmd < cmdl->n)
	{
		printf("\n\tCMD %li:\t\t\t%s\n", cmd, cmdl->cmd[cmd].raw);
		p = 0;
		while (p < cmdl->cmd[cmd].n)
		{
			printf("\n\t\tPIPE %li:\t\t%s\n", p, cmdl->cmd[cmd].p[p].raw);
			// printf("\n\t\tPIPE %li:\t\t%s\n", p, cmdl->cmd[cmd].p[p].cmd);
			printf("\n\t\tPIPE %li:\t\t%li\n", p, cmdl->cmd[cmd].p[p].n_arg);
			p++;
		}
		cmd++;
	}
	printf("\n");
}

/* TEST VOOR ENV */
// void	test_print_env(t_cmdl *cmdl)
// {
// 	size_t	i;

// 	i = 0;
// 	while (cmdl->env[i] != NULL)
// 	{
// 		printf("%s\n", cmdl->env[i]);
// 		i++;
// 	}
// }

// void	test_env(t_cmdl *cmdl)
// {
// 	printf("\nCHECK\t%s\n\n", return_ev(cmdl, "$?"));
// 	test_print_env(cmdl);
// 	printf("\nCHECK\t%s\nADD\n\n", return_ev(cmdl, "$?"));
// 	add_ev(cmdl, cmdl->input);
// 	test_print_env(cmdl);
// 	printf("\nCHECK\t%s\nREPLACE\n\n", return_ev(cmdl, "$?"));
// 	replace_ev(cmdl, "?=1");
// 	test_print_env(cmdl);
// 	printf("\nCHECK\t%s\nADD/REPLACE\n\n", return_ev(cmdl, "$?"));
// 	add_replace_ev(cmdl, "?=2");
// 	test_print_env(cmdl);
// 	printf("\nCHECK\t%s\nREMOVE\n\n", return_ev(cmdl, "$?"));
// 	remove_ev(cmdl, "?");
// 	test_print_env(cmdl);
// 	printf("\nCHECK\t%s\n\n", return_ev(cmdl, "$?"));
// }

int	main(int argc, char **argv, char **envp)
{
	t_cmdl	cmdl;

	copy_ev(&cmdl, envp);
	while (argc != 0 && argv[0] != NULL)
	{
		init_cmdl(&cmdl);
		cmdl.input = readline("MINISHELL> ");
		add_history(cmdl.input);
		if (empty_line(&cmdl) == false)
		{
			test_parsing(&cmdl);
			// test_env(&cmdl);
		}
		free_cmdl(&cmdl);
	}
}
