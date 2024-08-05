/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 22:22:09 by dkolida           #+#    #+#             */
/*   Updated: 2024/08/01 15:05:21 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_group	*group_init(int argc);
//static void		extract_infile(t_group *group);
int		add_to_group(t_shell *shell, t_group *group, char *token, int is_end);
int		shell_groups_init(t_shell *shell, char **tokens);

void	group_input(t_shell *shell, char **tokens)
{
	t_group	*group;
	int		tokens_count;
	int		i;

	tokens_count = shell_groups_init(shell, tokens);
	i = 0;
	group = NULL;
	while (tokens[i])
	{
		if (!group)
		{
			group = group_init(tokens_count);
			if (!group)
				return ;
		}
		if (add_to_group(shell, group, tokens[i], i == tokens_count - 1))
			group = NULL;
		i++;
	}
	shell->groups[shell->group_i] = NULL;
}

int	add_to_group(t_shell *shell, t_group *group, char *token, int is_end)
{
	if (ft_strcmp(token, "|") == 0 || is_end)
	{
		if (is_end && ft_strcmp(token, "|") != 0)
		{
			group->args[group->arg_i++] = ft_strdup(token);
			if (group->args[group->arg_i - 1] == NULL)
			{
				printf("Error: malloc failed\n");
			}
		}
		shell->groups[shell->group_i++] = group;
		shell->groups[shell->group_i] = NULL;
		return (1);
	}
	else
	{
		group->args[group->arg_i++] = ft_strdup(token);
		if (group->args[group->arg_i - 1] == NULL)
		{
			printf("Error: malloc failed\n");
		}
	}
	return (0);
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
	while (group->args[argc--])
		group->args[argc] = NULL;
	group->arg_i = 0;
	group->in_file_name = NULL;
	group->out_file_name = NULL;
	return (group);
}

int	shell_groups_init(t_shell *shell, char **tokens)
{
	int	tokens_count;

	tokens_count = 0;
	while (tokens[tokens_count])
		tokens_count++;
	shell->groups = malloc(sizeof(t_group *) * (tokens_count + 1));
	if (!shell->groups)
		return (0);
	shell->group_i = 0;
	return (tokens_count);
}
/*

static void	extract_infile(t_group *group)
{
	char	*filename;
	char	**split_group;
	char	*tmp;

	tmp = group->args;
	filename = ft_strchr(group->args, '<');
	if (filename == NULL)
		return ;
	split_group = ft_split(++filename, ' ');
	if (!split_group)
		return ;
	if (split_group[0])
	{
		group->in_file_name = ft_strdup(split_group[0]);
		if (!group->in_file_name)
			return ;
		while (*filename == ' ')
			filename++;
		group->args = ft_strdup(filename + ft_strlen(group->in_file_name));
		free(tmp);
	}
	else
		perror("Error: parse error near '<'");
	ft_free_split(split_group);
}

*/
