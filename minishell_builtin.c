/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_builtin.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/01 14:12:14 by rbom          #+#    #+#                 */
/*   Updated: 2024/08/15 19:04:39 by rbom          ########   odam.nl         */
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
			return (true);
		i++;
	}
}

void	execute_input(t_data *data)
{
	if (ft_strcmp(data->input_split[0], "echo"))
		echo_test(data);
	else if (ft_strcmp(data->input_split[0], "cd"))
		printf("%s: command not found (CD)\n", data->input_raw);
	else if (ft_strcmp(data->input_split[0], "pwd"))
		printf("%s: command not found (PWD)\n", data->input_raw);
	else if (ft_strcmp(data->input_split[0], "export"))
		printf("%s: command not found (EXPORT)\n", data->input_raw);
	else if (ft_strcmp(data->input_split[0], "unset"))
		printf("%s: command not found (UNSET)\n", data->input_raw);
	else if (ft_strcmp(data->input_split[0], "env"))
		printf("%s: command not found (ENV)\n", data->input_raw);
	else if (ft_strcmp(data->input_split[0], "exit"))
		exit_data(data, 0);
	else
		printf("%s: command not found (OTHER)\n", data->input_raw);
}

void	echo_test(t_data *data)
{
	size_t	i;

	i = 1;
	while (data->input_split[i] != NULL)
	{
		printf("%s ", data->input_split[i]);
		i++;
	}
	printf("\n");
}
