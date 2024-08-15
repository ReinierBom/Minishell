/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_input_line.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/01 14:12:14 by rbom          #+#    #+#                 */
/*   Updated: 2024/08/15 19:07:17 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	space(char c)
{
	if (c == ' '
		|| c == '\f'
		|| c == '\n'
		|| c == '\r'
		|| c == '\t'
		|| c == '\v')
		return (true);
	else
		return (false);
}

bool	empty_line(t_data *data)
{
	size_t	i;

	i = 0;
	while (data->input_raw != NULL && data->input_raw[i] != '\0')
	{
		if (space(data->input_raw[i]) == false)
			return (false);
		i++;
	}
	return (true);
}