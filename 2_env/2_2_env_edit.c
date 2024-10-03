/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   2_2_env_edit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/01 14:12:14 by rbom          #+#    #+#                 */
/*   Updated: 2024/10/02 15:01:35 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* ADDS TO ENV VAR */
static void	add_ev(t_cmdl *cmdl, char *str)
{
	size_t	i;
	char	**temp;

	i = 0;
	while (cmdl->env[i] != NULL)
		i++;
	temp = (char **)malloc((i + 2) * sizeof(char *));
	if (temp == NULL)
		exit_cmdl(cmdl, 1);
	i = 0;
	while (cmdl->env[i] != NULL)
	{
		temp[i] = cmdl->env[i];
		i++;
	}
	temp[i] = str;
	temp[i + 1] = NULL;
	free(cmdl->env);
	cmdl->env = temp;
}

/* CHECKS IF STR IS ENV VAR */
static bool	check_ev(t_cmdl *cmdl, char *str, size_t i)
{
	int	j;

	j = 0;
	while (cmdl->env[i][j] != '\0')
	{
		if (cmdl->env[i][j] == '=')
			return (true);
		else if (cmdl->env[i][j] == str[j])
			j++;
		else
			return (false);
	}
	return (false);
}

/* REPLACES VALUE ENV VAR */
static void	replace_ev(t_cmdl *cmdl, char *str)
{
	size_t	i;
	char	**temp;

	i = 0;
	while (cmdl->env[i] != NULL)
		i++;
	temp = (char **)malloc((i + 1) * sizeof(char *));
	if (temp == NULL)
		exit_cmdl(cmdl, 1);
	i = 0;
	while (cmdl->env[i] != NULL)
	{
		if (check_ev(cmdl, str, i) == false)
			temp[i] = cmdl->env[i];
		else
			temp[i] = str;
		i++;
	}
	temp[i] = NULL;
	free(cmdl->env);
	cmdl->env = temp;
}

/* REPLACES VALUE IF ENV VAR IS PRESENT, OTHERWISE ADDS */
void	add_replace_ev(t_cmdl *cmdl, char *str)
{
	int	i;

	i = 0;
	while (cmdl->env[i] != NULL)
	{
		if (check_ev(cmdl, str, i) == true)
		{
			replace_ev(cmdl, str);
			return ;
		}
		i++;
	}
	add_ev(cmdl, str);
}

/* REMOVES ENV VAR */
void	remove_ev(t_cmdl *cmdl, char *str)
{
	size_t	i;
	size_t	j;
	char	**temp;

	i = 0;
	while (cmdl->env[i] != NULL)
		i++;
	temp = (char **)malloc((i) * sizeof(char *));
	if (temp == NULL)
		exit_cmdl(cmdl, 1);
	i = 0;
	j = 0;
	while (cmdl->env[i] != NULL)
	{
		if (check_ev(cmdl, str, i) == false)
		{
			temp[j] = cmdl->env[i];
			j++;
		}
		i++;
	}
	temp[j] = NULL;
	free(cmdl->env);
	cmdl->env = temp;
}
