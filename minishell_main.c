/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_main.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/01 14:12:14 by rbom          #+#    #+#                 */
/*   Updated: 2024/09/13 15:53:10 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

void	test_parsing(t_cmdl *cmdl)
{
	size_t	i;
	size_t	j;
	// size_t	k;

	remove_par(cmdl);
	count_and_or(cmdl);
	split_and_or(cmdl);
	count_pipe(cmdl);
	split_pipe(cmdl);



	printf("\nINPUT:\t\t\t\t%s\n", cmdl->input);
	printf("\nNO_PAR:\t\t\t\t%s\n", cmdl->no_par);
	i = 0;
	while (i < cmdl->n)
	{
		printf("\n\tCMD %li:\t\t\t%s\n", i, cmdl->cmd[i].raw);
		j = 0;
		while (j < cmdl->cmd[i].n)
		{
			printf("\n\t\tPIPE %li:\t\t%s\n", j, cmdl->cmd[i].p[j].raw);
			// k = 0;
			// while (cmdl->cmd[i].p[j].raw[k] != '\0')
			// {
			// 	printf("\t\t\t\t\t\t%c\t%i\n", cmdl->cmd[i].p[j].raw[k], cmdl->cmd[i].p[j].raw[k]);
			// 	k++;
			// }
			j++;
		}
		i++;
	}
	printf("\n");
}





void	test_print_env(t_cmdl *cmdl)
{
	size_t	i;

	i = 0;
	while (cmdl->env[i] != NULL)
	{
		printf("%s\n", cmdl->env[i]);
		i++;
	}
}

void	test_env(t_cmdl *cmdl)
{
	printf("\nCHECK\t%s\n\n", return_ev(cmdl, "$?"));
	test_print_env(cmdl);
	printf("\nCHECK\t%s\nADD\n\n", return_ev(cmdl, "$?"));
	add_ev(cmdl, cmdl->input);
	test_print_env(cmdl);
	printf("\nCHECK\t%s\nREPLACE\n\n", return_ev(cmdl, "$?"));
	replace_ev(cmdl, "?=1");
	test_print_env(cmdl);
	printf("\nCHECK\t%s\nADD/REPLACE\n\n", return_ev(cmdl, "$?"));
	add_replace_ev(cmdl, "?=2");
	test_print_env(cmdl);
	printf("\nCHECK\t%s\nREMOVE\n\n", return_ev(cmdl, "$?"));
	remove_ev(cmdl, "?");
	test_print_env(cmdl);
	printf("\nCHECK\t%s\n\n", return_ev(cmdl, "$?"));
}









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
