/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_main.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/01 14:12:14 by rbom          #+#    #+#                 */
/*   Updated: 2024/08/01 14:40:45 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exit_loop(char *input)
{
	if (input[0] == 'e' && input[1] == 'x' && input[2] == 'i' && input[3] == 't' && (input[4] == ' ' || input[4] == '\0'))
		return (1);
	return (0);
}

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("MINISHELL> ");
		if (input && *input)
			add_history(input);
		if (exit_loop(input))
			break ;
		else if (input && *input)
			printf("%s: command not found\n", input);
		free(input);
	}
	free(input);
	return (0);
}
