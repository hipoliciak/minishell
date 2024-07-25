/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_wraper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:22:49 by dkolida           #+#    #+#             */
/*   Updated: 2024/07/22 23:12:54 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_read_line(char *line)
{
	if (line)
	{
		free (line);
		line = NULL;
	}
	line = readline("minishell> $ ");
	if (line && *line)
		add_history(line);
	return (line);
}
