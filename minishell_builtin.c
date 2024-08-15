/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_builtin.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/01 14:12:14 by rbom          #+#    #+#                 */
/*   Updated: 2024/08/15 16:54:32 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_strcmp(char *str_1, char *str_2)
{
	size_t	i;

	i = 0;
	while (true)
	{
		if (str_1[i] != str_2[i])
			return (false);
		if (str_1[i] == '\0')
			break ;
		i++;
	}
	return (true);
}

bool	check_builtin(t_data *data)
{
	if (ft_strcmp(data->input_split[0], "echo")
		|| ft_strcmp(data->input_split[0], "cd")
		|| ft_strcmp(data->input_split[0], "pwd")
		|| ft_strcmp(data->input_split[0], "export")
		|| ft_strcmp(data->input_split[0], "unset")
		|| ft_strcmp(data->input_split[0], "env")
		|| ft_strcmp(data->input_split[0], "exit"))
		return (true);
	else
		return (false);
}

void	execute_builtin(t_data *data)
{
	size_t	i;

	if (ft_strcmp(data->input_split[0], "exit"))
		data->exit = false;
	else if (ft_strcmp(data->input_split[0], "echo"))
	{
		i = 1;
		while (data->input_split[i] != NULL)
		{
			printf("%s ", data->input_split[i]);
			i++;
		}
		printf("\n");
	}
	else
		printf("%s: command not found (BUILTIN)\n", data->input_raw);
}

void	execute_other(t_data *data)
{
	printf("%s: command not found (OTHER)\n", data->input_raw);
}
