/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 23:51:06 by dkolida           #+#    #+#             */
/*   Updated: 2024/09/01 23:05:30 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokenizer	*tokenizer_init(int token_count)
{
	t_tokenizer	*data;

	data = malloc(sizeof(t_tokenizer));
	if (!data && free_tokenizer(data))
		return (NULL);
	data->tokens = malloc(sizeof(char *) * (token_count + 1));
	if (!data->tokens && free_tokenizer(data))
		return (NULL);
	data->not_interpolate = ft_calloc(token_count + 1, sizeof(int));
	if (!data->not_interpolate && free_tokenizer(data))
		return (NULL);
	data->token = ft_strdup("");
	if (!data->token && free_tokenizer(data))
		return (NULL);
	data->in_double_q = 0;
	data->in_single_q = 0;
	data->index = 0;
	return (data);
}
