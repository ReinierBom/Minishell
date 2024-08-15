/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_free.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/01 14:12:14 by rbom          #+#    #+#                 */
/*   Updated: 2024/08/15 18:41:08 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	null_data(t_data *data)
{
	data->input_raw = NULL;
	data->input_split = NULL;
}

void	free_data(t_data *data)
{
	size_t	i;

	if (data->input_raw != NULL)
		free(data->input_raw);
	if (data->input_split != NULL)
	{
		i = 0;
		while (data->input_split[i] != NULL)
		{
			free(data->input_split[i]);
			i++;
		}
		free(data->input_split);
	}
	null_data(data);
}

void	exit_data(t_data *data, size_t exit_code)
{
	free_data(data);
	rl_clear_history();
	exit(exit_code);
}
