/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 01:59:50 by dkolida           #+#    #+#             */
/*   Updated: 2024/08/27 18:29:28 by dkolida          ###   ########.fr       */
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
		while (j < groups[i]->arg_i)
		{
			printf("%s ", groups[i]->args[j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	free_groups(t_group **pipe_groups, int tokens_count)
{
	int	i;
	int	j;

	if (!pipe_groups)
		return ;
	i = 0;
	while (i < tokens_count)
	{
		j = 0;
		while (j <= tokens_count)
		{
			free(pipe_groups[i]->args[j]);
			pipe_groups[i]->args[j++] = NULL;
		}
		free(pipe_groups[i]->args);
		pipe_groups[i]->args = NULL;
		if (pipe_groups[i]->in_file_name)
			free(pipe_groups[i]->in_file_name);
		if (pipe_groups[i]->out_file_name)
			free(pipe_groups[i]->out_file_name);
		free(pipe_groups[i]);
		pipe_groups[i] = NULL;
		i++;
	}
	free(pipe_groups);
}

/*
void free_groups(t_group **pipe_groups, int tokens_count) {
    if (!pipe_groups)
        return;
    int i = 0;
    while (i < tokens_count) {
        if (pipe_groups[i]) {
            int j = 0;
            while (pipe_groups[i]->args && j <= tokens_count) {
                if (pipe_groups[i]->args[j]) {
                    free(pipe_groups[i]->args[j]);
                    pipe_groups[i]->args[j] = NULL;
                }
                j++;
            }
            if (pipe_groups[i]->args) {
                free(pipe_groups[i]->args);
                pipe_groups[i]->args = NULL;
            }
            if (pipe_groups[i]->in_file_name) {
                free(pipe_groups[i]->in_file_name);
                pipe_groups[i]->in_file_name = NULL;
            }
            if (pipe_groups[i]->out_file_name) {
                free(pipe_groups[i]->out_file_name);
                pipe_groups[i]->out_file_name = NULL;
            }
            free(pipe_groups[i]);
            pipe_groups[i] = NULL;
        }
        i++;
    }
    free(pipe_groups);
}
*/
