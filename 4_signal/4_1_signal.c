/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   4_1_signal.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/01 14:12:14 by rbom          #+#    #+#                 */
/*   Updated: 2024/10/03 19:07:56 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* SIGNAL HANDLERS */
static void	handle_sigint_ia(int sig)
{
	g_signal = sig;
	printf("\n");
	// rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	handle_sigquit_ia(int sig)
{
	(void)sig;
	rl_replace_line("  ", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	handle_sigint_nia(int sig)
{
	g_signal = sig;
	// printf("\n");
	// rl_replace_line("", 0);
	// rl_on_new_line();
	// rl_redisplay();
	// kill(0, g_signal);
}

static void	handle_sigquit_nia(int sig)
{
	g_signal = sig;
	// printf("Quit (core dumped)\n");
	// rl_replace_line("", 0);
	// rl_on_new_line();
	// rl_redisplay();
	// kill(0, g_signal);
}

/* INIT SIGNAL STRUCTS */
void	signal_mode(t_cmdl *cmdl, bool interactive)
{
	if (interactive == true)
	{
		cmdl->sa_int.sa_handler = &handle_sigint_ia;
		sigemptyset(&cmdl->sa_int.sa_mask);
		cmdl->sa_int.sa_flags = SA_RESTART;
		sigaction(SIGINT, &cmdl->sa_int, NULL);
		cmdl->sa_quit.sa_handler = &handle_sigquit_ia;
		sigemptyset(&cmdl->sa_quit.sa_mask);
		cmdl->sa_quit.sa_flags = SA_RESTART;
		sigaction(SIGQUIT, &cmdl->sa_quit, NULL);
	}
	else
	{
		cmdl->sa_int.sa_handler = &handle_sigint_nia;
		sigemptyset(&cmdl->sa_int.sa_mask);
		cmdl->sa_int.sa_flags = SA_RESTART;
		sigaction(SIGINT, &cmdl->sa_int, NULL);
		cmdl->sa_quit.sa_handler = &handle_sigquit_nia;
		sigemptyset(&cmdl->sa_quit.sa_mask);
		cmdl->sa_quit.sa_flags = SA_RESTART;
		sigaction(SIGQUIT, &cmdl->sa_quit, NULL);
	}
}
