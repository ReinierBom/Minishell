/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_main.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/01 14:12:14 by rbom          #+#    #+#                 */
/*   Updated: 2024/08/15 18:40:09 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_data	data;

	null_data(&data);
	data.exit_loop = true;
	while (data.exit_loop == true)
	{
		data.input_raw = readline("MINISHELL> ");
		if (empty_line(&data) == false)
		{
			add_history(data.input_raw);
			split_input(&data);
			if (check_builtin(&data))
				execute_builtin(&data);
			else
				execute_other(&data);
		}
		free_data(&data);
	}
	// rl_clear_history();
	// return (0);
	exit_data(&data, 0);
}
