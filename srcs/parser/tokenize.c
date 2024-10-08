/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:53:46 by dkolida           #+#    #+#             */
/*   Updated: 2024/09/14 19:10:03 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_spesials(char c, t_tokenizer *data);
static void	handle_quotes(char c, t_tokenizer *data);
static void	handle_quote(t_tokenizer *data, char c, int *other_q, int *this_q);

t_tokenizer	*get_tokens(t_shell *shell, char *input)
{
	t_tokenizer	*data;
	int			i;

	data = tokenizer_init(ft_strlen(input));
	if (!data)
		return (NULL);
	i = 0;
	while (input[i])
		handle_spesials(input[i++], data);
	if (*(data->token) != '\0')
		data->tokens[data->index++] = data->token;
	else if (data->token)
		free(data->token);
	data->token = NULL;
	data->tokens[data->index] = NULL;
	if ((data->index == 0 || data->in_double_q || data->in_single_q)
		&& free_tokenizer(data))
		return (NULL);
	interpolate(shell, data);
	return (data);
}

static void	handle_spesials(char c, t_tokenizer *data)
{
	if (ft_strchr("|><; '\"", c))
	{
		if (c == '"' || c == '\'')
			handle_quotes(c, data);
		else if (ft_strchr("|><; ", c)
			&& !data->in_double_q
			&& !data->in_single_q)
		{
			if (*(data->token) != '\0')
			{
				data->tokens[data->index++] = data->token;
				data->token = ft_strdup("");
			}
			if (ft_isprint(c) && c > ' ')
				data->tokens[data->index++] = char_to_str(c);
		}
		else
			data->token = ft_strjoin_char(data->token, c);
	}
	else
		data->token = ft_strjoin_char(data->token, c);
}

static void	handle_quotes(char c, t_tokenizer *data)
{
	if (c == '"')
		handle_quote(data, c, &data->in_single_q, &data->in_double_q);
	else
		handle_quote(data, c, &data->in_double_q, &data->in_single_q);
}

static void	handle_quote(t_tokenizer *data, char c, int *other_q, int *this_q)
{
	if (*other_q)
		data->token = ft_strjoin_char(data->token, c);
	else
	{
		if (*this_q)
		{
			if (c == '\'')
				data->not_interpolate[data->index] = 1;
			*this_q = 0;
		}
		else
			*this_q = 1;
	}
}
