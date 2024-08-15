/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 17:10:47 by rbom          #+#    #+#                 */
/*   Updated: 2024/08/15 18:40:20 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_data
{
	char	*input_raw;
	char	**input_split;
	bool	exit_loop;
}	t_data;

/* minishell_input_line.c */
bool	space(char c);
bool	empty_line(t_data *data);

/* minishell_input_split.c */
void	split_input(t_data *data);

/* minishell_builtin.c */
bool	ft_strcmp(char *str_1, char *str_2);
bool	check_builtin(t_data *data);
void	execute_builtin(t_data *data);
void	execute_other(t_data *data);

/* minishell_free.c */
void	null_data(t_data *data);
void	free_data(t_data *data);
void	exit_data(t_data *data, size_t exit_code);

#endif
