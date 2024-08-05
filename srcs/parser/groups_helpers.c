/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 01:59:50 by dkolida           #+#    #+#             */
/*   Updated: 2024/08/01 14:53:13 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_groups(t_group **groups)
{
	int	i;
	int	j;

	i = 0;
	while (groups[i])
	{
		j = 0;
		printf("group %d:", i);
		while (groups[i]->args[j])
		{
			printf("%s ", groups[i]->args[j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	free_groups(t_group **pipe_groups)
{
	int	i;

	if (!pipe_groups)
		return ;
	i = 0;
	while (pipe_groups[i])
	{
		if (pipe_groups[i]->args)
		{
			while (pipe_groups[i]->arg_i--)
				free(pipe_groups[i]->args[pipe_groups[i]->arg_i]);
			free(pipe_groups[i]->args);
			free(pipe_groups[i]);
		}
		i++;
	}
	free(pipe_groups);
}
