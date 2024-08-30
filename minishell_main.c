/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_main.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/01 14:12:14 by rbom          #+#    #+#                 */
/*   Updated: 2024/08/30 18:49:09 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

int	main(void)
{
	t_data	data;

	set_sigaction(&data);
	while (true)
	{
		null_data(&data);
		data.input_raw = readline("MINISHELL> ");
		if (empty_line(&data) == false)
		{
			add_history(data.input_raw);
			// split_input(&data);
			execute_input(&data);
		}
		free_data(&data);
	}
}
