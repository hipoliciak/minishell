/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 23:07:00 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/08/30 02:04:59 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_builtin(t_shell *shell)
{
	char	*path;

	(void)shell;
	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("pwd");
		exit(1);
	}
	ft_putendl_fd(path, shell->out_fd);
	free(path);
	shell->last_exit_code = 0;
	return (0);
}
