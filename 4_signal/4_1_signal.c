/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   4_1_signal.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/01 14:12:14 by rbom          #+#    #+#                 */
/*   Updated: 2024/10/02 20:24:08 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// SIGINT handler (Ctrl-C) for interactive mode
void sigint_handler_interactive(int signo) {
    rl_replace_line("", 0);  // Clear the current input line
    rl_on_new_line();        // Move to a new line
    rl_redisplay();          // Redisplay the prompt
}

// SIGQUIT handler (Ctrl-\) for interactive mode (do nothing)
void sigquit_handler_interactive(int signo) {
    // Ignore Ctrl-\ in interactive mode
}

void signal_interactive_mode(struct sigaction sa_int, struct sigaction sa_quit) {
    // Set up SIGINT (Ctrl-C) handler for interactive mode
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_handler = sigint_handler_interactive;
    sa_int.sa_flags = SA_RESTART;  // Restart interrupted system calls
    sigaction(SIGINT, &sa_int, NULL);

    // Set up SIGQUIT (Ctrl-\) handler for interactive mode
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_handler = sigquit_handler_interactive;
    sa_quit.sa_flags = 0;  // No special flags
    sigaction(SIGQUIT, &sa_quit, NULL);
}

void signal_non_interactive_mode(struct sigaction sa_int, struct sigaction sa_quit) {
    // Restore default SIGINT (Ctrl-C) behavior in non-interactive mode
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_handler = SIG_DFL;  // Default signal handler
    sigaction(SIGINT, &sa_int, NULL);

    // Restore default SIGQUIT (Ctrl-\) behavior in non-interactive mode
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_handler = SIG_DFL;  // Default signal handler
    sigaction(SIGQUIT, &sa_quit, NULL);
}










/* SIGNAL HANDLERS */
static void	handle_sigint_ia(int sig)
{
	g_signal = sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	handle_sigquit_ia(int sig)
{
	g_signal = sig;
	// printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	handle_sigint_nia(int sig)
{
	g_signal = sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	kill(0, g_signal);
}

static void	handle_sigquit_nia(int sig)
{
	g_signal = sig;
	printf("Quit (core dumped)\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	kill(0, g_signal);
}




// /* SIGNAL HANDLERS */
// static void	handle_sigint_ia(int sig)
// {
// 	g_signal = sig;
// 	printf("\n^C\n");
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// }

// static void	handle_sigquit_ia(int sig)
// {
// 	g_signal = sig;
// 	return;
// }

// static void	handle_sigint_nia(int sig)
// {
// 	g_signal = sig;
// 	printf("^C\n");
// 	kill(0, SIGINT);
// }

// static void	handle_sigquit_nia(int sig)
// {
// 	g_signal = sig;
// 	printf("^\\Quit (core dumped)\n");
// 	kill(0, SIGQUIT);
// }




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
