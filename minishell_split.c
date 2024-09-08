/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_split_cmd.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 14:37:56 by rbom          #+#    #+#                 */
/*   Updated: 2024/09/08 14:58:15 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static size_t	check_quote(size_t quote, char c)
// {
// 	if (quote == 0 && c == '\'')
// 		return (1);
// 	else if (quote == 0 && c == '"')
// 		return (2);
// 	else if ((quote == 1 && c == '\'') || (quote == 2 && c == '"'))
// 		return (0);
// }

// static size_t	check_and_or(char c1, char c2)
// {
// 	if (c1 == '&' && c2 == '&')
// 		return (1);
// 	else if (c1 == '|' && c2 == '|')
// 		return (2);
// 	else
// 		return (0);
// }

// static void	counter(t_cmdl *cmdl)
// {
// 	size_t	i;
// 	size_t	quote;
// 	size_t	and_or;

// 	i = 0;
// 	quote = 0;
// 	cmdl->n = 1;
// 	while (quote == 1 || cmdl->input[i] != '\0')
// 	{
// 		quote = check_quote(quote, cmdl->input[i]);
// 		and_or = check_and_or(cmdl->input[i], cmdl->input[i + 1]);
// 		if (quote == 0 && and_or > 0)
// 		{
// 			cmdl->n++;
// 			i += 2;
// 		}
// 		else
// 			i++;
// 	}
// }




// static size_t	cut_raw(t_cmdl *cmdl, size_t start)
// {
// 	size_t	i;
// 	size_t	quote;
// 	size_t	and_or;

// 	i = 0;
// 	quote = 0;
// 	and_or = check_and_or(cmdl->input[start + i], cmdl->input[start + i + 1]);
// 	while (quote == 1 || (cmdl->input[start + i] != '\0' && and_or == 0))



// 		len++;
// 	return (len);
// }

// static void	score_and_or(t_cmdl *cmdl)
// {
// 	size_t	i;
// 	size_t	cmd;
// 	size_t	quote;
// 	size_t	and_or;

// 	i = 0;
// 	cmd = 0;
// 	quote = 0;
// 	cmdl->cmd[cmd].and_or = 0;
// 	while (quote == 1 || cmdl->input[i] != '\0')
// 	{
// 		quote = check_quote(quote, cmdl->input[i]);
// 		and_or = check_and_or(cmdl->input[i], cmdl->input[i + 1]);
// 		if (quote == 0 && and_or > 0)
// 		{
// 			cmd++;
// 			cmdl->cmd[cmd].and_or = and_or;
// 			i += 2;
// 		}
// 		else
// 			i++;
// 	}
// }










// // static size_t	find_len(t_cmdl *cmdl, size_t start)	/* DONE! */
// // {
// // 	size_t	len;

// // 	len = 0;
// // 	while (cmdl->input[start + len] != '\0'
// // 		&& ((cmdl->input[start + len] != '&'
// // 				&& cmdl->input[start + len + 1] != '&')
// // 			|| (cmdl->input[start + len] != '|'
// // 				&& cmdl->input[start + len + 1] != '|')))
// // 		len++;
// // 	return (len);
// // }

// static char	*find_word(t_cmdl *cmdl, size_t start, size_t len)
// {
// 	char	*word;
// 	size_t	i;

// 	word = (char *)malloc((len + 1) * sizeof(char));
// 	if (word == NULL)
// 		exit_data(data, 2);
// 	i = 0;
// 	while (i < len)
// 	{
// 		word[i] = data->input_raw[start + i];
// 		i++;
// 	}
// 	word[len] = '\0';
// 	return (word);
// }





// void	split_cmdl(t_cmdl *cmdl)
// {
// 	size_t	cmd;
// 	size_t	start;
// 	size_t	len;

// 	counter(cmdl);
// 	cmdl->cmd = (t_cmd *)malloc(cmdl->n * sizeof(t_cmd));
// 	if (cmdl->cmd == NULL)
// 		exit_data(cmdl, 1);




// 	cmd = 0;
// 	start = 0;
// 	while (cmd < cmdl->n)
// 	{
// 		len = find_len(cmdl, start);
// 		cmdl->cmd[cmd] = find_word(data, start, len);
// 		cmd++;
// 		start += len + 2;
// 	}
// }
