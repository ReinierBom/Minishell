/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_signal.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/01 14:12:14 by rbom          #+#    #+#                 */
/*   Updated: 2024/08/30 20:02:33 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sig(int sig)
{
	g_signal = sig;
	if (g_signal == SIGQUIT)
		printf("Quit (core dumped)");
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

// void	null_sigaction(t_data *data)
// {
// 	data->sa_int.sa_handler = SIG_DFL;
// 	data->sa_quit.sa_handler = SIG_DFL;
// 	sigemptyset(&data->sa_int.sa_mask);
// 	sigemptyset(&data->sa_quit.sa_mask);
// 	data->sa_int.sa_flags = 0;
// 	data->sa_quit.sa_flags = 0;
// 	sigaction(SIGINT, &data->sa_int, NULL);
// 	sigaction(SIGQUIT, &data->sa_quit, NULL);
// }

void	set_sigaction(t_data *data)
{
	data->sa_int.sa_handler = &handle_sig;
	data->sa_quit.sa_handler = &handle_sig;
	sigemptyset(&data->sa_int.sa_mask);
	sigemptyset(&data->sa_quit.sa_mask);
	data->sa_int.sa_flags = SA_RESTART;
	data->sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGINT, &data->sa_int, NULL);
	sigaction(SIGQUIT, &data->sa_quit, NULL);
}
