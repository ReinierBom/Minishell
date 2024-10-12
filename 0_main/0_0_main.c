/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   0_0_main.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/01 14:12:14 by rbom          #+#    #+#                 */
/*   Updated: 2024/10/11 17:48:45 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_exit;

int	main(int argc, char **argv, char **envp)
{
	t_cmdl	cmdl;

	init_start(&cmdl, envp);
	while (argc != 0 && argv[0] != NULL)
	{
		init_cmdl(&cmdl);
		cmdl.input = readline("MINISHELL> ");
		if (check_input(&cmdl) == false)
			continue ;
		parse_cmdl(&cmdl);
		test_parsing_cmdl(&cmdl);
		run_sub(&cmdl);
		free_cmdl(&cmdl);
	}
}
