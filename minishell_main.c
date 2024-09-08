/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_main.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/01 14:12:14 by rbom          #+#    #+#                 */
/*   Updated: 2024/09/08 15:11:41 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

// int	main(int argc, char **argv, char **envp)
// {
// 	t_cmdl	cmdl;

// 	while (argc != 0 && argv[0] != NULL)
// 	{
// 		null_cmdl(&cmdl, envp);
// 		cmdl.input = readline("MINISHELL> ");
// 		add_history(cmdl.input);
// 		if (empty_line(&cmdl) == false)
// 		{
// 			split_cmdl(&cmdl);
// 			// execute_input(&cmdl);
// 		}
// 		free_cmdl(&cmdl);
// 	}
// }



char	*env_var(t_cmdl *cmdl, char *str)
{
	int	i;
	int	j;

	if (str[0] != '$')
		return (str);		
	i = 0;
	while (cmdl->env[i] != NULL)
	{
		j = 0;
		while (cmdl->env[i][j] != '\0')
		{
			if (cmdl->env[i][j] == str[j + 1])
				j++;
			else if (cmdl->env[i][j] == '=')
				return (cmdl->env[i] + j + 1);
			else
				break ;
		}
		i++;
	}
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmdl	cmdl;

	while (argc != 0 && argv[0] != NULL)
	{
		init_cmdl(&cmdl, envp);
		cmdl.input = readline("MINISHELL> ");
		printf("%s\n", env_var(&cmdl, cmdl.input));
	}
}
