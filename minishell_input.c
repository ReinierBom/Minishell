/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_input.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/01 14:12:14 by rbom          #+#    #+#                 */
/*   Updated: 2024/09/13 18:47:34 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* CHECKS IF SPACE */
bool	space(char c)
{
	if (c == ' '
		|| c == '\f'
		|| c == '\n'
		|| c == '\r'
		|| c == '\t'
		|| c == '\v')
		return (true);
	else
		return (false);
}

/* CHECKS EMPTY INPUT */
bool	empty_line(t_cmdl *cmdl)
{
	size_t	i;

	if (cmdl->input == NULL)				/* THIS IS CTRL-D! */
		exit_cmdl(cmdl, 0);
	i = 0;
	while (cmdl->input[i] != '\0')
	{
		if (space(cmdl->input[i]) == false)
			return (false);
		i++;
	}
	return (true);
}
