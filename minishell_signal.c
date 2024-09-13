/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_signal.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/01 14:12:14 by rbom          #+#    #+#                 */
/*   Updated: 2024/09/13 14:34:58 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	handle_sigint_ia(int sig)
// {
// 	g_signal = sig;
// 	printf("\n");
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// }

// void	handle_sigquit_ia(int sig)
// {
// 	g_signal = sig;
// 	// printf("\n");
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// }

// void	handle_sigint_nia(int sig)
// {
// 	g_signal = sig;
// 	printf("\n");
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// 	kill(0, g_signal);
// }

// void	handle_sigquit_nia(int sig)
// {
// 	g_signal = sig;
// 	printf("Quit (core dumped)\n");
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// 	kill(0, g_signal);
// }









// void	handle_sigint_ia(int sig)
// {
// 	g_signal = sig;
// 	printf("\n^C\n");
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// }

// void	handle_sigquit_ia(int sig)
// {
// 	g_signal = sig;
// 	return;
// }

// void	handle_sigint_nia(int sig)
// {
// 	g_signal = sig;
// 	printf("^C\n");
// 	kill(0, SIGINT);
// }

// void	handle_sigquit_nia(int sig)
// {
// 	g_signal = sig;
// 	printf("^\\Quit (core dumped)\n");
// 	kill(0, SIGQUIT);
// }






// void	signal_ia_mode(t_cmdl *cmdl)
// {
// 	cmdl->sa_int.sa_handler = &handle_sigint_ia;
// 	sigemptyset(&cmdl->sa_int.sa_mask);
// 	cmdl->sa_int.sa_flags = SA_RESTART;
// 	sigaction(SIGINT, &cmdl->sa_int, NULL);


// 	cmdl->sa_quit.sa_handler = &handle_sigquit_ia;
// 	sigemptyset(&cmdl->sa_quit.sa_mask);
// 	cmdl->sa_quit.sa_flags = SA_RESTART;
// 	sigaction(SIGQUIT, &cmdl->sa_quit, NULL);
// }

// void	signal_nia_mode(t_cmdl *cmdl)
// {
// 	cmdl->sa_int.sa_handler = &handle_sigint_nia;
// 	sigemptyset(&cmdl->sa_int.sa_mask);
// 	cmdl->sa_int.sa_flags = SA_RESTART;
// 	sigaction(SIGINT, &cmdl->sa_int, NULL);


// 	cmdl->sa_quit.sa_handler = &handle_sigquit_nia;
// 	sigemptyset(&cmdl->sa_quit.sa_mask);
// 	cmdl->sa_quit.sa_flags = SA_RESTART;
// 	sigaction(SIGQUIT, &cmdl->sa_quit, NULL);
// }



