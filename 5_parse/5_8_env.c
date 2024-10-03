/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   5_8_env.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 14:37:56 by rbom          #+#    #+#                 */
/*   Updated: 2024/10/02 18:00:53 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	len_env_var(char *str, size_t i)
{
	size_t	len;

	len = 1;
	if (str[i + len] == '_' || (str[i + len] >= 'A' && str[i + len] <= 'Z') || (str[i + len] >= 'a' && str[i + len] <= 'z'))
	{
		len++;
		while (str[i + len] == '_' || (str[i + len] >= '0' && str[i + len] <= '9') || (str[i + len] >= 'A' && str[i + len] <= 'Z') || (str[i + len] >= 'a' && str[i + len] <= 'z'))
			len++;
	}
	else if (str[i + len] == '?' || (str[i + len] >= '0' && str[i + len] <= '9') || str[i + len] == '?' || str[i + len] == '$' || str[i + len] == '!' || str[i + len] == '#' || str[i + len] == '@' || str[i + len] == '*' || str[i + len] == '-')
		len++;
	else if (str[i + len] == '{')
	{
		len++;
		while (str[i + len] >= '0' && str[i + len] <= '9')
			len++;
		if (str[i + len] == '}')
			len++;
	}
	return (len);
}

static size_t	len_non_env_var(char *str, size_t quote, size_t i)
{
	size_t	len;

	len = 0;
	while ((quote > 0 || str[i + len] != '\0') && (quote == 1 || str[i + len] != '$'))
	{
		len++;
		quote = check_quote(quote, str[i + len]);
	}
	return (len);
}

static size_t	quote_non_env_var(char *str, size_t quote, size_t i)
{
	size_t	len;

	len = 0;
	while ((quote > 0 || str[i + len] != '\0') && (quote == 1 || str[i + len] != '$'))
	{
		len++;
		quote = check_quote(quote, str[i + len]);
	}
	return (quote);
}

static char	**count_env_var(t_cmdl *cmdl, char *str)
{
	size_t	i;
	size_t	len;
	size_t	count;
	size_t	quote;
	char	**str_arr;

	i = 0;
	count = 0;
	quote = 0;
	while (quote > 0 || str[i] != '\0')
	{
		count++;
		quote = check_quote(quote, str[i]);
		if (quote != 1 && str[i] == '$')
			len = len_env_var(str, i);
		else
		{
			len = len_non_env_var(str, quote, i);
			quote = quote_non_env_var(str, quote, i);
		}
		i += len;
	}
	str_arr = malloc(count * sizeof(char *));
	if (str_arr == NULL)
		exit_cmdl(cmdl, 1);
	return (str_arr);
}

char	*split_env_var(t_cmdl *cmdl, char *str)
{
	char	**str_arr;
	size_t	i;
	size_t	start;
	size_t	len;
	size_t	count;
	size_t	quote;

	str_arr = count_env_var(cmdl, str);
	start = 0;
	count = 0;
	quote = 0;
	while (quote > 0 || str[start] != '\0')
	{
		quote = check_quote(quote, str[start]);
		if (quote != 1 && str[start] == '$')
			len = len_env_var(str, start);
		else
		{
			len = len_non_env_var(str, quote, start);
			quote = quote_non_env_var(str, quote, start);
		}
		str_arr[count] = (char *)malloc(len + 1);
		if (str_arr[count] == NULL)
			exit_cmdl(cmdl, 1);
		i = 0;
		while (i < len)
		{
			str_arr[count][i] = str[start + i];
			i++;
		}
		str_arr[count][i] = '\0';
		str_arr[count] = replace_ev_str(cmdl, str_arr[count]);
		start += len;
		count++;
	}
	str = concat_str(cmdl, str_arr, count);
	return (str);
}
