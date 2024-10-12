/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   5_2_env_1.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 14:37:56 by rbom          #+#    #+#                 */
/*   Updated: 2024/10/12 19:56:06 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	len_env_var(char *str, size_t start)
{
	size_t	len;

	len = start + 1;
	if (str[len] == '_' || (str[len] >= 'A' && str[len] <= 'Z')
		|| (str[len] >= 'a' && str[len] <= 'z'))
	{
		len++;
		while (str[len] == '_' || (str[len] >= '0' && str[len] <= '9')
			|| (str[len] >= 'A' && str[len] <= 'Z')
			|| (str[len] >= 'a' && str[len] <= 'z'))
			len++;
	}
	else if (str[len] == '?' || (str[len] >= '0' && str[len] <= '9')
		|| str[len] == '$' || str[len] == '!' || str[len] == '#'
		|| str[len] == '@' || str[len] == '*' || str[len] == '-')
		len++;
	else if (str[len] == '{')
	{
		len++;
		while (str[len] >= '0' && str[len] <= '9')
			len++;
		if (str[len] == '}')
			len++;
	}
	return (len - start);
}

size_t	len_non_env_var(char *str, size_t quote, size_t start)
{
	size_t	len;

	len = start;
	while ((quote > 0 || str[len] != '\0') && (quote == 1 || str[len] != '$'))
	{
		len++;
		quote = check_quote(quote, str[len]);
	}
	return (len - start);
}

size_t	quote_env_var(char *str, size_t quote, size_t start, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		i++;
		quote = check_quote(quote, str[start + i]);
	}
	return (quote);
}

char	**count_env_var(t_cmdl *cmdl, char *str)
{
	size_t	i;
	size_t	len;
	size_t	count;
	size_t	quote;
	char	**str_arr;

	i = 0;
	count = 0;
	quote = check_quote(0, str[i]);
	while (quote > 0 || str[i] != '\0')
	{
		count++;
		if (quote != 1 && str[i] == '$')
			len = len_env_var(str, i);
		else
			len = len_non_env_var(str, quote, i);
		quote = quote_env_var(str, quote, i, len);
		i += len;
	}
	str_arr = malloc(count * sizeof(char *));
	if (str_arr == NULL)
		exit_cmdl(cmdl, 1, false);
	return (str_arr);
}

char	*copy_env_var(t_cmdl *cmdl, char *line, size_t len, size_t start)
{
	char	*str;
	size_t	i;

	str = (char *)malloc(len + 1);
	if (str == NULL)
		exit_cmdl(cmdl, 1, false);
	i = 0;
	while (i < len)
	{
		str[i] = line[start + i];
		i++;
	}
	str[i] = '\0';
	str = replace_ev_str(cmdl, str);
	return (str);
}
