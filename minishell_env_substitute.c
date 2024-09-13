/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_env_substitute.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/01 14:12:14 by rbom          #+#    #+#                 */
/*   Updated: 2024/09/12 19:40:53 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_ev(t_cmdl *cmdl, char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	cmdl->env = (char **)malloc((i + 1) * sizeof(char *));
	i = 0;
	while (envp[i] != NULL)
	{
		cmdl->env[i] = envp[i];
		i++;
	}
	cmdl->env[i] = NULL;
}

char	*return_ev(t_cmdl *cmdl, char *str)
{
	int	i;
	int	j;

	if (str[0] != '$')
		return (str);
	i = 0;
	while (cmdl->env[i] != NULL)
	{
		j = 0;
		while (cmdl->env[i][j] != '\0')
		{
			if (cmdl->env[i][j] == str[j + 1])
				j++;
			else if (cmdl->env[i][j] == '=')
				return (cmdl->env[i] + j + 1);
			else
				break ;
		}
		i++;
	}
	return (NULL);
}

void	replace_ev_str(t_cmdl *cmdl, char *str)
{
	char	*temp;

	if (str != return_ev(cmdl, str))
	{
		temp = return_ev(cmdl, str);
		free(str);
		str = temp;
	}
}

void	replace_ev_arr(t_cmdl *cmdl, char **arr, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		replace_ev_str(cmdl, arr[i]);
		i++;
	}
}
