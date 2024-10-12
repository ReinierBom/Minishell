/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   5_9_quote.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 14:37:56 by rbom          #+#    #+#                 */
/*   Updated: 2024/10/12 21:05:21 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*len_quote(t_cmdl *cmdl, char *str)
{
	char	*no_quote;
	size_t	i;
	size_t	len;
	size_t	quote;

	i = 0;
	len = 0;
	quote = 0;
	while (str[i] != '\0')
	{
		quote = check_quote(quote, str[i]);
		if (!(quote == 0 && (str[i] == '\'' || str[i] == '"'))
			&& !(quote == 1 && str[i] == '\'')
			&& !(quote == 2 && str[i] == '"'))
			len++;
		i++;
	}
	no_quote = (char *)malloc(len +1);
	if (no_quote == NULL)
		exit_cmdl(cmdl, 1, false);
	return (no_quote);
}

char	*remove_quote(t_cmdl *cmdl, char *str)
{
	char	*no_quote;
	size_t	i;
	size_t	len;
	size_t	quote;

	no_quote = len_quote(cmdl, str);
	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		quote = check_quote(quote, str[i]);
		if (!(quote == 0 && (str[i] == '\'' || str[i] == '"'))
			&& !(quote == 1 && str[i] == '\'')
			&& !(quote == 2 && str[i] == '"'))
		{
			no_quote[len] = str[i];
			len++;
		}
		i++;
	}
	no_quote[len] = '\0';
	free(str);
	return (no_quote);
}
