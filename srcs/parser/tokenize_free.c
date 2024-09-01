/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 23:51:40 by dkolida           #+#    #+#             */
/*   Updated: 2024/09/01 22:19:22 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

int	free_tokenizer(t_tokenizer *tokenizer)
{
	if (!tokenizer)
		return (1);
	if (tokenizer->tokens != NULL)
	{
		ft_free_split(tokenizer->tokens);
	}
	if (tokenizer->not_interpolate != NULL)
	{
		free(tokenizer->not_interpolate);
		tokenizer->not_interpolate = NULL;
	}
	if (tokenizer->token != NULL)
	{
		free(tokenizer->token);
		tokenizer->token = NULL;
	}
	free(tokenizer);
	tokenizer = NULL;
	return (1);
}
