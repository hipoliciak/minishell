/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 22:22:09 by dkolida           #+#    #+#             */
/*   Updated: 2024/09/02 00:01:28 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_group	*group_init(int argc);
void	add_to_group(t_shell *shell, char *token, int is_end);
void	shell_groups_init(t_shell *shell, int tokens_count);

void	group_input(t_shell *shell, t_tokenizer *data)
{
	int	i;
	int	*grp_i;

	grp_i = &shell->group_i;
	shell_groups_init(shell, data->index);
	shell->tokens_count = data->index;
	i = 0;
	while (data->tokens[i])
	{
		if (!shell->groups[*grp_i])
			shell->groups[*grp_i] = group_init(shell->tokens_count);
		if (ft_strcmp(data->tokens[i], "<") == 0 && data->tokens[i])
			shell->groups[*grp_i]->in_file_name = ft_strdup(data->tokens[++i]);
		else if (ft_strcmp(data->tokens[i], ">") == 0)
			shell->groups[*grp_i]->out_file_name = ft_strdup(data->tokens[++i]);
		else
			add_to_group(shell, data->tokens[i], i == shell->tokens_count - 1);
		i++;
	}
	if (*grp_i > 0)
		(*grp_i)--;
}
//The group_i variable is used to keep track of the current group index later.

void	add_to_group(t_shell *shell, char *token, int is_end)
{
	int	*i;
	int	*arg_i;

	i = &shell->group_i;
	arg_i = &shell->groups[*i]->arg_i;
	if (ft_strcmp(token, "|") == 0 || is_end)
	{
		if ((is_end && ft_strcmp(token, "|") != 0)
			|| (((*arg_i) > 0)
				&& (ft_strcmp(shell->groups[*i]->args[(*arg_i) - 1], "echo")
					== 0)))
			shell->groups[*i]->args[(*arg_i)++] = ft_strdup(token);
		(*i)++;
	}
	else
		shell->groups[*i]->args[(*arg_i)++] = ft_strdup(token);
}

t_group	*group_init(int argc)
{
	t_group	*group;

	group = malloc(sizeof(t_group));
	if (!group)
		return (NULL);
	group->args = malloc(sizeof(char *) * (argc + 1));
	if (!group->args)
	{
		free(group);
		return (NULL);
	}
	while (argc >= 0)
		group->args[argc--] = NULL;
	group->arg_i = 0;
	group->in_file_name = NULL;
	group->out_file_name = NULL;
	return (group);
}

void	shell_groups_init(t_shell *shell, int tokens_count)
{
	int	i;

	shell->groups = malloc(sizeof(t_group *) * (tokens_count + 1));
	if (!shell->groups)
		return ;
	shell->group_i = 0;
	i = 0;
	while (i < tokens_count)
		shell->groups[i++] = NULL;
}
