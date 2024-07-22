/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:21:53 by dkolida           #+#    #+#             */
/*   Updated: 2024/07/23 00:56:18 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig_num)
{
	(void)sig_num;
	rl_replace_line("\n", 0);
	ft_putendl_fd("", 1);
	rl_on_new_line();
	rl_redisplay();
}
