/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:53:46 by dkolida           #+#    #+#             */
/*   Updated: 2024/07/25 12:58:17 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_spesials(char c, char **tokens, int *t, char *current_token, int *in_double_quotes, int *in_single_quotes);

char	**tokenize(char *input)
{
	char	**tokens;
	char	*current_token;
	int		in_double_quotes;
	int		in_single_quotes;
	int		i;
	int		t;

	tokens = malloc(sizeof(char *) * (ft_strlen(input) + 1));
	if (!tokens)
		return (NULL);
	current_token = ft_strdup("");
	in_double_quotes = 0;
	in_single_quotes = 0;
	i = 0;
	t = 0;
	while (input[i])
	{
		if (ft_strchr("|><; '\"", input[i]))
			current_token = handle_spesials(input[i], tokens, &t, current_token, &in_double_quotes, &in_single_quotes);
		else
			current_token = ft_strjoin_char(current_token, input[i]);
		i++;
	}
	if (*current_token != '\0')
		tokens[t++] = current_token;
	tokens[t] = NULL;
	if (in_double_quotes || in_single_quotes)
	{
		ft_free_split(tokens);
		tokens = NULL;
		perror("Error: unclosed quotes");
	}
	return (tokens);
}

static char	*handle_spesials(char c, char **tokens, int *t, char *current_token, int *in_double_quotes, int *in_single_quotes)
{
	if (c == ' ' && !*in_double_quotes && !*in_single_quotes)
	{
		if (*current_token != '\0')
		{
			tokens[(*t)++] = current_token;
			current_token = ft_strdup("");
		}
	}
	else if (c == '"' || c == '\'')
	{
		if (c == '"')
		{
			if (*in_single_quotes)
				current_token = ft_strjoin_char(current_token, c);
			else
			{
				if (*in_double_quotes)
				{
					tokens[(*t)++] = current_token;
					current_token = ft_strdup("");
				}
				*in_double_quotes = !*in_double_quotes;
			}
		}
		else
		{
			if (*in_double_quotes)
				current_token = ft_strjoin_char(current_token, c);
			else
			{
				if (*in_single_quotes)
				{
					tokens[(*t)++] = current_token;
					current_token = ft_strdup("");
				}
				*in_single_quotes = !*in_single_quotes;
			}
		}
	}
	else if (ft_strchr("|><;", c) && !*in_double_quotes && !*in_single_quotes)
	{
		if (*current_token != '\0')
		{
			tokens[(*t)++] = current_token;
			current_token = ft_strdup("");
		}
		if (ft_isprint(c))
			tokens[(*t)++] = char_to_str(c);
	}
	else
		current_token = ft_strjoin_char(current_token, c);
	return (current_token);
}
