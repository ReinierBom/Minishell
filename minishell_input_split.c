/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_input_split.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbom <rbom@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 14:37:56 by rbom          #+#    #+#                 */
/*   Updated: 2024/08/15 16:53:20 by rbom          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	counter(t_data *data)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (data->input_raw[i] != '\0')
	{
		if (space(data->input_raw[i]) == false
			&& (i == 0 || space(data->input_raw[i - 1]) == true))
			count++;
		i++;
	}
	return (count);
}

static size_t	find_start(t_data *data, size_t start)
{
	while (space(data->input_raw[start]) == true)
		start++;
	return (start);
}

static size_t	find_len(t_data *data, size_t start)
{
	size_t	len;

	len = 1;
	while (data->input_raw[start + len] != '\0'
		&& space(data->input_raw[start + len]) == false)
		len++;
	return (len);
}

static char	*find_word(t_data *data, size_t start, size_t len)
{
	char	*word;
	size_t	i;
	
	word = (char *)malloc(len + 1 * sizeof(char));
	if (word == NULL)
		exit(2);													/* ERROR */
	i = 0;
	while (i < len)
	{
		word[i] = data->input_raw[start + i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

void	split_input(t_data *data)
{
	size_t	count;
	size_t	word;
	size_t	start;
	size_t	len;

	count = counter(data);
	data->input_split = (char **)malloc(count + 1 * sizeof(char *));
	if (data->input_split == NULL)
		exit(1);													/* ERROR */
	word = 0;
	start = 0;
	while (word < count)
	{
		start = find_start(data, start);
		len = find_len(data, start);
		data->input_split[word] = find_word(data, start, len);
		word++;
		start += len + 1;
	}
	data->input_split[count] = NULL;
}
