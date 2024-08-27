/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 23:07:00 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/08/27 23:04:30 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	pwd_builtin(t_shell *shell)
// {
// 	char	*path;

// 	(void)shell;
// 	path = getcwd(NULL, 0);
// 	if (!path)
// 	{
// 		perror("pwd");
// 		return (1);
// 	}
// 	ft_putendl_fd(path, 1);
// 	free(path);
// 	return (0);
// }

void	pwd_builtin(t_shell *shell)
{
	char	*path;

	(void)shell;
	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("pwd");
		exit(1);
	}
	ft_putendl_fd(path, 1);
	free(path);
}
