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
	// g_signal = 0;
	// signal_ia_mode(cmdl);
	cmdl->input = NULL;
	cmdl->no_par = NULL;
	cmdl->n = 0;
	cmdl->cmd = NULL;
}

void	free_cmdl(t_cmdl *cmdl)
{
	if (cmdl->input != NULL)
		free(cmdl->input);
	if (cmdl->no_par != NULL)
		free(cmdl->no_par);
}

void	exit_cmdl(t_cmdl *cmdl, size_t exit_code)
{
	free_cmdl(cmdl);
	rl_clear_history();
	exit(exit_code);
}
