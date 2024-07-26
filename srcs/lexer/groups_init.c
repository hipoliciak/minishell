/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 22:22:09 by dkolida           #+#    #+#             */
/*   Updated: 2024/07/26 01:06:04 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_group	*group_init(char *group);
static void		extract_infile(t_group *group);

t_group	**group_input(char *line)
{
	t_group	**groups;
	char	**str_groups;
	int		group_count;
	int		i;

	str_groups = ft_split(line, '|');
	if (!str_groups)
		return (NULL);
	group_count = 0;
	while (str_groups[group_count])
		group_count++;
	groups = malloc(sizeof(t_group *) * (group_count + 1));
	if (!groups)
		return (NULL);
	i = 0;
	while (str_groups[i])
	{
		if (*str_groups[i] != '\0')
			groups[i] = group_init(str_groups[i]);
		i++;
	}
	groups[i] = NULL;
	free(str_groups);
	return (groups);
}

static t_group	*group_init(char *group)
{
	t_group	*new_group;

	if (!group)
		return (NULL);
	new_group = malloc(sizeof(t_group));
	if (!new_group)
		return (NULL);
	new_group->str = group;
	new_group->in_file_name = NULL;
	extract_infile(new_group);
	new_group->out_file_name = NULL;
	return (new_group);
}

static void	extract_infile(t_group *group)
{
	char	*filename;
	char	**split_group;
	char	*tmp;

	tmp = group->str;
	filename = ft_strchr(group->str, '<');
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
		group->str = ft_strdup(filename + ft_strlen(group->in_file_name));
		free(tmp);
	}
	else
		perror("Error: parse error near '<'");
	ft_free_split(split_group);
}
