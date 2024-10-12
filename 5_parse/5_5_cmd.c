/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   5_5_cmd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 14:37:56 by rbom          #+#    #+#                 */
/*   Updated: 2024/10/12 20:30:25 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* LENGTH COMMAND */
size_t	len_cmd(t_pipe *pipe)
{
	size_t	len;
	size_t	quote;

	len = 0;
	quote = check_quote(0, pipe->line[len]);
	while (quote > 0 || (pipe->line[len] != '<' && pipe->line[len] != '>'
			&& pipe->line[len] != '\0' && space(pipe->line[len]) == false))
	{
		len++;
		quote = check_quote(quote, pipe->line[len]);
	}
	return (len);
}

/* COPIES COMMAND */
void	copy_cmd(t_cmdl *cmdl, t_pipe *pipe)
{
	size_t	len;
	size_t	i;
	size_t	quote;

	len = len_cmd(pipe);
	if (len == 0)
		return ;
	pipe->cmd = (char *)malloc(len + 1);
	if (pipe->cmd == NULL)
		exit_cmdl(cmdl, 1, false);
	i = 0;
	quote = check_quote(0, pipe->line[i]);
	while (quote > 0 || (pipe->line[i] != '<' && pipe->line[i] != '>'
			&& pipe->line[i] != '\0' && space(pipe->line[i]) == false))
	{
		pipe->cmd[i] = pipe->line[i];
		i++;
		quote = check_quote(quote, pipe->line[i]);
	}
	pipe->cmd[i] = '\0';
	pipe->cmd = remove_quote(cmdl, pipe->cmd);
}
