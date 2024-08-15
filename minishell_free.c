/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_free.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/01 14:12:14 by rbom          #+#    #+#                 */
/*   Updated: 2024/08/15 18:17:11 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_data(t_data *data)
{
	data->exit_loop = true;
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
}

void	exit_data(t_data *data, size_t exit_code)
{
	free_data(data);
	exit(exit_code);
}