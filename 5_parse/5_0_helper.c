/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   5_0_helper.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 14:37:56 by rbom          #+#    #+#                 */
/*   Updated: 2024/10/02 17:08:37 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* CHECKS IF STR IS QUOTED */
size_t	check_quote(size_t quote, char c)
{
	if (quote == 0 && c == '\'')
		return (1);
	else if (quote == 1 && c == '\'')
		return (0);
	else if (quote == 0 && c == '"')
		return (2);
	else if (quote == 2 && c == '"')
		return (0);
	else
		return (quote);
}

static size_t	count_space(char *str)
{
	size_t	start;
	size_t	len;

	start = 0;
	len = 0;
	while (space(str[start]))
		start++;
	while (str[start + len] != '\0')
		len++;
	while (len > 0 && space(str[start + len - 1]))
		len--;
	return (len);
}

char	*remove_space(t_cmdl *cmdl, char *str)
{
	size_t	len;
	char	*no_space;
	size_t	start;
	size_t	i;

	len = count_space(str);
	no_space = (char *)malloc(len + 1);
	if (no_space == NULL)
		exit_cmdl(cmdl, 1);
	start = 0;
	i = 0;
	while (space(str[start]))
		start++;
	while (i < len)
	{
		no_space[i] = str[start + i];
		i++;
	}
	no_space[len] = '\0';
	free(str);
	return (no_space);
}
