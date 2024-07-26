/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:53:46 by dkolida           #+#    #+#             */
/*   Updated: 2024/07/25 16:38:11 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokenizer	*init_tokenizer_data(int token_count);
static void	handle_spesials(char c, t_tokenizer *data);
static void	handle_quotes(char c, t_tokenizer *data);
static void	handle_quote(t_tokenizer *data, char c, int *other_q, int *this_q);

char	**tokenize(char *input)
{
	t_tokenizer	*data;
	int			i;
	char		**tokens;

	data = init_tokenizer_data(ft_strlen(input));
	if (!data)
		return (NULL);
	i = 0;
	while (input[i])
		handle_spesials(input[i++], data);
	if (*(data->token) != '\0')
		data->tokens[data->index++] = data->token;
	else
		free(data->token);
	data->tokens[data->index] = NULL;
	if (data->in_double_q || data->in_single_q)
	{
		ft_free_split(data->tokens);
		perror("Error: unclosed quotes");
		return (NULL);
	}
	tokens = data->tokens;
	free(data);
	return (tokens);
}

t_tokenizer	*init_tokenizer_data(int token_count)
{
	t_tokenizer	*data;

	data = malloc(sizeof(t_tokenizer));
	if (!data)
		return (NULL);
	data->tokens = malloc(sizeof(char *) * (token_count + 1));
	if (!data->tokens)
	{
		free(data);
		return (NULL);
	}
	data->token = ft_strdup("");
	if (!data->token)
	{
		free(data->tokens);
		free(data);
		return (NULL);
	}
	data->in_double_q = 0;
	data->in_single_q = 0;
	data->index = 0;
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
			data->tokens[data->index++] = data->token;
			data->token = ft_strdup("");
		}
		*this_q = !*this_q;
	}
}
