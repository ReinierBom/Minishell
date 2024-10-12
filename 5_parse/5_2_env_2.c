/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   5_2_env_2.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 14:37:56 by rbom          #+#    #+#                 */
/*   Updated: 2024/10/12 20:15:21 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*concat_len(t_cmdl *cmdl, char **str_arr, size_t n)
{
	size_t	i;
	size_t	len;
	size_t	count;
	char	*str;

	len = 0;
	count = 0;
	while (count < n)
	{
		i = 0;
		while (str_arr[count][i] != '\0')
		{
			i++;
			len++;
		}
		count++;
	}
	str = (char *)malloc(len + 1);
	if (str == NULL)
		exit_cmdl(cmdl, 1, false);
	return (str);
}

char	*concat_str(t_cmdl *cmdl, char **str_arr, size_t n)
{
	size_t	i;
	size_t	len;
	size_t	count;
	char	*str;

	str = concat_len(cmdl, str_arr, n);
	len = 0;
	count = 0;
	while (count < n)
	{
		i = 0;
		while (str_arr[count][i] != '\0')
		{
			str[len] = str_arr[count][i];
			i++;
			len++;
		}
		count++;
	}
	str[len] = '\0';
	free(str_arr);
	return (str);
}

void	split_env_var(t_cmdl *cmdl, t_cmd *cmd)
{
	char	**str_arr;
	size_t	start;
	size_t	len;
	size_t	count;
	size_t	quote;

	str_arr = count_env_var(cmdl, cmd->line);
	if (str_arr == NULL)
		exit_cmdl(cmdl, 1, false);
	start = 0;
	count = 0;
	quote = check_quote(0, cmd->line[start]);
	while (quote > 0 || cmd->line[start] != '\0')
	{
		if (quote != 1 && cmd->line[start] == '$')
			len = len_env_var(cmd->line, start);
		else
			len = len_non_env_var(cmd->line, quote, start);
		quote = quote_env_var(cmd->line, quote, start, len);
		str_arr[count] = copy_env_var(cmdl, cmd->line, len, start);
		start += len;
		count++;
	}
	cmd->line = concat_str(cmdl, str_arr, count);
}
