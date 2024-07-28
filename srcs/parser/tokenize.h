/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 23:55:18 by dkolida           #+#    #+#             */
/*   Updated: 2024/07/28 03:32:51 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

# include "minishell.h"

typedef struct s_tokenizer
{
	char	**tokens;
	int		index;
	char	*token;
	int		in_double_q;
	int		in_single_q;
	int		*not_interpolate;
}	t_tokenizer;

t_tokenizer	*tokenizer_init(int token_count);
int			free_tokenizer(t_tokenizer *tokenizer);
void		interpolate(t_shell *shell, t_tokenizer *data);

#endif
