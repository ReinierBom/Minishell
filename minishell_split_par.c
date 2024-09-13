/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_split_1.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 14:37:56 by rbom          #+#    #+#                 */
/*   Updated: 2024/09/12 14:43:01 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	check_quote(size_t quote, char c)
{
	if (quote == 0 && c == '\'')
		return (1);
	else if (quote == 0 && c == '"')
		return (2);
	else if ((quote == 1 && c == '\'') || (quote == 2 && c == '"'))
		return (0);
	else
		return (quote);
}

size_t	count_par(t_cmdl *cmdl)
{
	size_t	i;
	size_t	n;
	size_t	quote;

	i = 0;
	n = 0;
	quote = 0;
	while (quote > 0 || i == 0 || cmdl->input[i - 1] != '\0')
	{
		quote = check_quote(quote, cmdl->input[i]);
		if (quote == 0 && (cmdl->input[i] == '(' || cmdl->input[i] == ')'))
			n++;
		i++;
	}
	return (i - n);
}

void	remove_par(t_cmdl *cmdl)
{
	size_t	i;
	size_t	j;
	size_t	quote;

	cmdl->no_par = malloc(count_par(cmdl));
	if (cmdl->no_par == NULL)
		exit_cmdl(cmdl, 1);
	i = 0;
	j = 0;
	quote = 0;
	while (quote > 0 || i == 0 || cmdl->input[i - 1] != '\0')
	{
		quote = check_quote(quote, cmdl->input[i]);
		if (quote > 0 || (cmdl->input[i] != '(' && cmdl->input[i] != ')'))
		{
			cmdl->no_par[j] = cmdl->input[i];
			j++;
		}
		i++;
	}
}
