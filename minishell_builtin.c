/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_builtin.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/01 14:12:14 by rbom          #+#    #+#                 */
/*   Updated: 2024/08/30 18:43:38 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_strcmp(char *str_1, char *str_2)
{
	size_t	i;

	i = 0;
	while (true)
	{
		if ((str_1[i] == '\0' || str_1[i] == ' ') && str_2[i] == '\0')
			return (true);
		if (str_1[i] != str_2[i])
			return (false);
		i++;
	}
}

void	execute_input(t_data *data)
{
	if (ft_strcmp(data->input_raw, "echo"))
		echo_test(data);
	else if (ft_strcmp(data->input_raw, "cd"))
		printf("%s: command not found (CD)\n", data->input_raw);
	else if (ft_strcmp(data->input_raw, "pwd"))
		printf("%s: command not found (PWD)\n", data->input_raw);
	else if (ft_strcmp(data->input_raw, "export"))
		printf("%s: command not found (EXPORT)\n", data->input_raw);
	else if (ft_strcmp(data->input_raw, "unset"))
		printf("%s: command not found (UNSET)\n", data->input_raw);
	else if (ft_strcmp(data->input_raw, "env"))
		printf("%s: command not found (ENV)\n", data->input_raw);
	else if (ft_strcmp(data->input_raw, "exit"))
		exit_data(data, 0);
	else
		printf("%s: command not found (OTHER)\n", data->input_raw);
}

void	echo_test(t_data *data)
{
	printf("%s ", data->input_raw);
	printf("\n");
}
